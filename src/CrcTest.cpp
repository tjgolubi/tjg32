#include "CrcEngine.h"
#include "CrcClasses.hpp"

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

template<class Crc>
bool Test() {
  if (Crc::bits != 32)
    return true;
  using namespace std;
  cout << "Testing " << Crc::Name << endl;
  Crc crc;
  crc.update(TestBuf);
  if (crc.value() == Crc::Check)
    return true;

  cout << hex << setfill('0');
  int width = 2 * sizeof(typename Crc::CrcType);
  cout << "Returned value is not as expected."
      << "\nBits         =   " << dec << Crc::bits << hex
      << "\nPoly         = 0x" << setw(width) << Value(Crc::poly)
      << "\nDir          =   " << ((Crc::dir == tjg::CrcDir::LsbFirst) ? "LSB" : "MSB")
      << "\nCheck        = 0x" << setw(width) << Value(Crc::Check)
      << "\nCrc          = 0x" << setw(width) << Value(crc.value())
      << "\nReflect(Crc) = 0x" << setw(width) << Value(tjg::Reflect(crc.value()))
      << endl;
  return false;
} // Test

int main() {
  meta::ForEachType<tjg::AllCrcAlgorithms>([&]<typename Crc>() {
    (void) Test<Crc>();
  });
  return EXIT_SUCCESS;
} // main
