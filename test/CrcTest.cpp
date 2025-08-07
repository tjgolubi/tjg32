#include "CrcKnown.hpp"

#include "../tjg/SaveIo.hpp"

#include <iostream>
#include <iomanip>

#include <concepts>
#include <type_traits>
#include <cstddef>
#include <cstdlib>

alignas(8) constexpr auto TestBuf = std::array<std::byte, 9>{
  std::byte{'1'}, std::byte{'2'}, std::byte{'3'},
  std::byte{'4'}, std::byte{'5'}, std::byte{'6'},
  std::byte{'7'}, std::byte{'8'}, std::byte{'9'}
}; // TestBuf

template<std::unsigned_integral U>
struct CoutType: public std::conditional<(sizeof(U) == 1), unsigned, U> { };

template<std::unsigned_integral U>
auto Value(U x) -> typename CoutType<U>::type
  { return static_cast<typename CoutType<U>::type>(x); }

template<class CrcTraits>
bool Test() {
  using namespace std;
  auto saveIo = tjg::SaveIo{cout};
  using Crc = tjg::crc::Known<CrcTraits>;
  cout << "Testing " << Crc::Name;
  Crc crc;
  crc.update(TestBuf);
  if (crc.value() == Crc::Check) {
    cout << " PASSED" << endl;
    return true;
  }

  tjg::SetHex(cout);
  int width = 2 * sizeof(typename Crc::value_type);
  cout << "\nReturned value is not as expected."
    << "\nBits         =   " << dec << Crc::Bits << hex
    << "\nPoly         = 0x" << setw(width) << Value(Crc::Poly)
    << "\nDir          =   "
    << ((Crc::Dir == tjg::crc::Endian::LsbFirst) ? "LSB" : "MSB")
    << "\nCheck        = 0x" << setw(width) << Value(Crc::Check)
    << "\nCrc          = 0x" << setw(width) << Value(crc.value())
    << "\nReflect(Crc) = 0x" << setw(width) << Value(tjg::Reflect(crc.value()))
      << endl;
  return false;
} // Test

int main() {
  int failCount = 0;

  using Crcs = tjg::crc::test_detail::KnownCrcs;

  meta::ForEachType<Crcs>([&]<typename CrcTraits>() {
    if (!Test<CrcTraits>())
      ++failCount;
  });

  std::cout << failCount << '/' << meta::LengthV<Crcs>
            << " tests failed." << std::endl;
  return (failCount == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
} // main
