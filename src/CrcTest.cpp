#include "CrcEngine.h"
#include "CrcKnown.h"
#include "CrcTraits.h"
#include "SaveIo.h"

#include <iostream>
#include <iomanip>

#include <concepts>
#include <type_traits>
#include <cstddef>
#include <cstdlib>

constexpr auto TestBuf = std::array<std::byte, 9>{
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
  using Crc = tjg::CrcKnown<CrcTraits>;
  cout << "Testing " << Crc::Name << endl;
  Crc crc;
  crc.update(TestBuf);
  if (crc.value() == Crc::Check)
    return true;

  tjg::SetHex(cout);
  int width = 2 * sizeof(typename Crc::CrcType);
  cout << "Returned value is not as expected."
    << "\nBits         =   " << dec << Crc::bits << hex
    << "\nPoly         = 0x" << setw(width) << Value(Crc::poly)
    << "\nDir          =   "
    << ((Crc::dir == tjg::CrcDir::LsbFirst) ? "LSB" : "MSB")
    << "\nCheck        = 0x" << setw(width) << Value(Crc::Check)
    << "\nCrc          = 0x" << setw(width) << Value(crc.value())
    << "\nReflect(Crc) = 0x" << setw(width) << Value(tjg::Reflect(crc.value()))
      << endl;
  return false;
} // Test

int main() {
  int failCount = 0;

//  using Crcs = tjg::Known32BitCrcs;
  using Crcs = tjg::KnownCrcs;

  meta::ForEachType<Crcs>([&]<typename CrcTraits>() {
    if (!Test<CrcTraits>())
      ++failCount;
  });

  std::cout << failCount << '/' << meta::LengthV<Crcs>
            << " tests failed." << std::endl;
  return (failCount == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
} // main
