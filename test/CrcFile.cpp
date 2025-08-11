#include "crc/CrcFile.hpp"
#include "crc/CrcKnown.hpp"

#include "tjg/SaveIo.hpp"

#include <chrono>
#include <filesystem>
#include <vector>
#include <random>
#include <string_view>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <utility>
#include <cstddef>
#include <cstdlib>

using Clock = std::chrono::high_resolution_clock;

constexpr auto BufSize  = std::size_t{  1 << 10};
constexpr auto FileSize = std::size_t{100 << 20};
constexpr auto ExpectedCrc = std::uint32_t{0x7f6ef538};

int main() {
  namespace fs = std::filesystem;
  try {
    constexpr auto Seed = 12345;
    std::mt19937 rng{Seed};
    rng.seed(Seed);

    auto dataCrc = tjg::crc::Known<tjg::crc::Crc32IsoHdlc>{};

    const auto fname = fs::path{"crc.tmp"};
    if (exists(fname) && file_size(fname) == FileSize) {
      std::cout << fname.generic_string() << " already exists.\n";
    } else {

      using namespace std;
      auto saveIo = tjg::SaveIo{cerr};

      auto out = ofstream{};
      out.exceptions(ofstream::failbit | ofstream::badbit);
      out.open(fname, std::ios::out | std::ios::binary);
      cerr << "Writing file with random bytes " << flush;
      auto buf = vector<char>{};
      buf.reserve(BufSize);
      size_t written =  0;
      for ( ; written < FileSize; written += BufSize) {
        buf.clear();
        for (size_t j = 0; j != BufSize; ++j)
          buf.push_back(static_cast<char>(rng() & 0xff));
        dataCrc.update(buf);
        out.write(data(buf), ssize(buf));
      }
      cerr << ' ' << written << " done crc=0x" << hex << setfill('0')
           << setw(8) << dataCrc.value()
           << endl;
      if (dataCrc.value() != ExpectedCrc) {
        cout << "CRC of data is not as expected (0x"
             << setw(8) << ExpectedCrc << ')' << endl;
      }
      out.close();
    }
    {
      using namespace std;
      auto saveId = tjg::SaveIo{cerr};
      cerr << "Running FileCrc..." << flush;
      auto start = Clock::now();
      auto fileCrc = tjg::crc::FileCrc(fname);
      auto stop  = Clock::now();
      tjg::SetHex(cerr);
      cerr << " done crc=0x" << setw(8) << fileCrc.value() << dec << ' ' << fileCrc.value() << endl;
      auto s = chrono::duration<double>(stop - start);
      if (s.count() == 0.0) {
        cout << "Rate = infinite\n";
      } else {
        auto rate = FileSize / s.count();
        cout << "Rate = " << (rate/(1<<20)) << " MiB/s\n";
      }
      if (fileCrc != ExpectedCrc) {
        cout << "Failed." << endl;
        return EXIT_FAILURE;
      }
    }

    return EXIT_SUCCESS;
  }
  catch (std::exception& x) {
    std::cerr << "Caught exception: " << x.what() << std::endl;
  }
  catch (...) {
    std::cerr << "Caught unknown exception" << std::endl;
  }
  return EXIT_FAILURE;
} // main
