/// @file
/// @copyright 2025 Terry Golubiewski, all rights reserved.
/// @author Terry Golubiewski
///
/// Google Test for file CRC computation and POSIX cksum
/// compatibility.
///
/// Generates a deterministic random file, checks the CRC computed while writing
/// against the CRC read back from disk, and (optionally) compares to coreutils
/// "cksum".
///
/// Notes: - The first in-memory CRC compare against ExpectedCrc is
/// informational only.  It helps establish or notice changes in the "golden"
/// value.  The required check is that the FileCrc equals the in-memory CRC from
/// generation.
///
/// - Uses std::chrono::high_resolution_clock intentionally.
///
/// - Seed is a command-line parameter: --crc-seed=<N>.  If not provided,
///   DefaultSeed is used.  The ExpectedCrc warning is shown when the seed is
///   default, including when explicitly requested via --crc-seed=<DefaultSeed>.

#include "crc/CrcFile.hpp"
#include "crc/CrcKnown.hpp"

#include "tjg/SaveIo.hpp"

#include <File.hpp>

#include <gtest/gtest.h>

#include <chrono>
#include <filesystem>
#include <random>
#include <string>
#include <string_view>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstddef>

namespace fs = std::filesystem;

namespace {

constexpr auto DefaultBufSize  = std::size_t{1 << 10}; // 1 KiB
constexpr auto DefaultFileSize = std::size_t{100 << 20}; // 100 MiB
constexpr auto ExpectedCrc     = std::uint32_t{0x7f6ef538};

// Command-line seed handling.
constexpr auto DefaultSeed = std::uint32_t{12345};
static std::uint32_t Seed = DefaultSeed;

// Parse --crc-seed=<N> before RUN_ALL_TESTS()
void ParseArgsAndInitSeed(int* argc, char** argv) {
  for (int i = 1; i < *argc; ++i) {
    std::string_view arg{argv[i]};
    if (arg.rfind("--crc-seed=", 0) == 0) {
      try {
        Seed = static_cast<std::uint32_t>(
                                      std::stoul(std::string(arg.substr(11))));
      } catch (...) {
        std::cerr << "Invalid --crc-seed; using DefaultSeed.\n";
      }
      // Remove arg so GTest does not see it.
      for (int j = i; j < *argc - 1; ++j) argv[j] = argv[j + 1];
      --(*argc);
      break;
    }
  }
}

// Writes file with deterministic pseudorandom data, updating CRC
// as it goes.  Returns the in-memory CRC.  Overwrites existing.
std::uint32_t WriteTestFile(const fs::path& fname,
                            std::size_t fileSize, std::size_t bufSize)
{
  using namespace std;
  auto out = ofstream{};
  out.exceptions(ofstream::failbit | ofstream::badbit);
  out.open(fname, ios::out | ios::binary | ios::trunc);

  auto rng = std::mt19937{Seed};

  auto dataCrc = tjg::crc::Known<tjg::crc::Crc32IsoHdlc, tjg::crc::MaxSlices>{};

  auto buf = std::vector<char>{};
  buf.reserve(bufSize);

  for (std::size_t written = 0; written < fileSize; written += bufSize) {
    buf.clear();
    for (std::size_t j = 0; j != bufSize; ++j)
      buf.push_back(static_cast<char>(rng() & 0xff));
    dataCrc.update(buf);
    out.write(std::data(buf), std::ssize(buf));
  }
  out.close();
  return dataCrc.value();
}

// Try to run coreutils `cksum` and parse the CRC field (first
// number).  Returns pair<ok, value>.
std::pair<bool, std::uint32_t> RunCoreutilsCksum(const fs::path& fname) {
  std::string line;

  {
    std::string cmd = "cksum ";
    cmd += fname.generic_string();
    auto pipe = tjg::Pipe{cmd, "r"};
    if (!pipe) return {false, 0};
    char buf[256] = {0};
    while (pipe.gets(buf, sizeof(buf)))
      line += buf;
    (void) pipe.close();
  }

  // Expected format: "<crc> <size> <path>\n"
  unsigned long long crc = 0;
  unsigned long long size = 0;
  if (std::sscanf(line.c_str(), "%llu %llu", &crc, &size) == 2)
    return {true, static_cast<std::uint32_t>(crc)};
  return {false, 0};
} // RunCoreutilsCksum

struct FileCrcTest: ::testing::Test {
  fs::path tmp;
  std::size_t fileSize = 0;
  std::size_t bufSize  = 0;

  void SetUp() override {
    fileSize = DefaultFileSize;
    bufSize  = DefaultBufSize;
    // Make a simple temp filename in the temp directory.
    auto base = std::string{"crc_gtest_"};
    base += std::to_string(static_cast<unsigned long>(Seed));
    base += ".tmp";
    tmp = fs::temp_directory_path() / fs::path{base};
  }

  void TearDown() override {
    std::error_code ec;
    fs::remove(tmp, ec);
  }
};

TEST_F(FileCrcTest, FileCrcMatchesGenerationCrc) {
  using namespace std;
  auto dataCrc = WriteTestFile(tmp, fileSize, bufSize);

  // Informational: show ExpectedCrc mismatch only when using the
  // default seed, whether implied or explicitly specified.
  if (Seed == DefaultSeed && dataCrc != ExpectedCrc) {
    auto saveIo = tjg::SaveIo{cout};
    tjg::SetHex(cout);
    cout << "Note: data CRC 0x" << setw(8) << setfill('0')
         << dataCrc << " != ExpectedCrc 0x" << setw(8)
         << ExpectedCrc << '\n';
  }

  auto fileCrc = tjg::crc::FileCrc(tmp);

  EXPECT_EQ(fileCrc.value(), dataCrc);
}

TEST_F(FileCrcTest, FileCksumMatchesCoreutilsIfAvailable) {
  // Prepare file
  (void) WriteTestFile(tmp, fileSize, bufSize);

  // tjg::crc::FileCksum should match coreutils cksum CRC.
  auto ours = tjg::crc::FileCksum(tmp);

  auto [ok, theirs] = RunCoreutilsCksum(tmp);
  if (!ok) {
    GTEST_SKIP() << "coreutils cksum not available on this system";
  }

  EXPECT_EQ(ours.value(), theirs);
}

} // local

int main(int argc, char** argv) {
  ParseArgsAndInitSeed(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
