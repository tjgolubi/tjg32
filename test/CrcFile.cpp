#include "crc/CrcFile.hpp"
#include "crc/CrcKnown.hpp"

#include "tjg/SaveIo.hpp"

#include <chrono>
#include <filesystem>
#include <vector>
#include <random>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <utility>
#include <cstddef>
#include <cstdlib>

using Clock = std::chrono::high_resolution_clock;

constexpr auto BufSize  = std::size_t{  1 << 10};
constexpr auto FileSize = std::size_t{100 << 20};

int main() {
  namespace fs = std::filesystem;
  try {
      constexpr auto Seed = 12345;
      std::mt19937 rng{Seed};
      rng.seed(Seed);
 
    // auto dataCrc = tjg::crc::FastCrc32{};

    const auto fname = fs::path{"crc.tmp"};
    if (exists(fname) && file_size(fname) == FileSize) {
      std::cout << fname.generic_string() << " already exists.\n";
    } else {
      using namespace std;
      // auto saveIo = tjg::SaveIo{cerr};

      auto out = ofstream{fname};
      if (!out.is_open() || out.fail())
        throw ofstream::failure{fname.generic_string() + " opening"};
      // out.exceptions(ofstream::failbit | ofstream::badbit);
      cerr << "Writing file with random bytes " << flush;
      auto buf = vector<char>{};
      buf.reserve(BufSize);
      size_t written =  0;
      for ( ; written < FileSize; written += BufSize) {
        buf.clear();
        for (size_t j = 0; j != BufSize; ++j)
          buf.push_back(static_cast<char>(rng() & 0xff));
        // dataCrc.update(buf);
        if (!out.write(data(buf), ssize(buf)))
          throw ofstream::failure{fname.generic_string() + " writing"};
      }
      // tjg::SetHex(cerr);
      cerr << ' ' << written << " done " // crc=0x" << hex << setw(8) << dataCrc.value()
           << endl;
    }
    std::cerr << "Outside of block" << std::flush;

#if 0
    {
      using namespace std;
      auto saveId = tjg::SaveIo{cerr};
      cerr << "Running FileCrc..." << flush;
      auto start = Clock::now();
      auto fileCrc = 0ul; // tjg::crc::FileCrc(fname, tjg::crc::FastCrc32{});
      auto stop  = Clock::now();
      tjg::SetHex(cerr);
      cerr << " done crc=0x" << setw(8) << fileCrc << endl;
      auto s = chrono::duration<double>(stop - start);
      if (s.count() > 0) {
        cout << "Rate = infinite\n";
      } else {
        auto rate = FileSize / s.count();
        cout << "Rate = " << rate << " MiB/s\n";
      }
      if (fileCrc != dataCrc) {
        cout << "Failed." << endl;
        return EXIT_FAILURE;
      }
    }
#endif

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
