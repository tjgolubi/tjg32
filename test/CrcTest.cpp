#include "crc/CrcKnown.hpp"

#include "tjg/SaveIo.hpp"

#include <iostream>
#include <iomanip>

#include <concepts>
#include <type_traits>
#include <cstddef>
#include <cstdlib>

template<std::unsigned_integral U>
struct CoutType: public std::conditional<(sizeof(U) == 1), unsigned, U> { };

template<std::unsigned_integral U>
auto Value(U x) -> typename CoutType<U>::type
  { return static_cast<typename CoutType<U>::type>(x); }

alignas(16) constexpr auto TestBuf = std::array<std::byte, 9>{
  std::byte{'1'}, std::byte{'2'}, std::byte{'3'},
  std::byte{'4'}, std::byte{'5'}, std::byte{'6'},
  std::byte{'7'}, std::byte{'8'}, std::byte{'9'}
}; // TestBuf

template<std::size_t N>
constexpr std::array<std::byte, N> GenerateData() {
  std::array<std::byte, N> result;
  for (std::size_t i = 0; i != N; ++i)
    result[i] = std::byte((i+1) & 0xff);
  return result;
} // GenerateData

constinit auto TestData = GenerateData<256>();

template<class CrcTraits, std::size_t Slices>
void PrintFailure(const tjg::crc::Known<CrcTraits, Slices>& crc,
                  typename CrcTraits::value_type expected)
{
  using namespace std;
  using Crc = tjg::crc::Known<CrcTraits>;
  auto saveIo = tjg::SaveIo{cout};
  tjg::SetHex(cout);
  int width = 2 * sizeof(typename Crc::value_type);
  cout << "\nReturned value is not as expected."
    << "\nBits         =   " << dec << Crc::Bits << hex
    << "\nPoly         = 0x" << setw(width) << Value(Crc::Poly)
    << "\nDir          =   "
    << ((Crc::Dir == tjg::crc::Endian::LsbFirst) ? "LSB" : "MSB")
    << "\nSlices       =   " << Slices
    << "\nCheck        = 0x" << setw(width) << Value(crc.value())
    << "\nCrc          = 0x" << setw(width) << Value(expected)
    << "\nReflect(Crc) = 0x" << setw(width) << Value(
                                            tjg::bit_reverse(crc.value()))
    << endl;
} // PrintFailure

template<class CrcTraits, std::size_t N=TestData.size(), std::size_t Offset=0>
requires (N > 0 && N + Offset <= TestData.size())
bool TestSize() {
  using namespace std;
  auto saveIo = tjg::SaveIo{cout};
  using Crc0 = tjg::crc::Known<CrcTraits, 0>;
  using Crc  = tjg::crc::Known<CrcTraits>;
  constexpr auto Data = span{TestData.data()+Offset, N};
  Crc0 crc0;
  crc0.update(Data);
  Crc crc;
  crc.update(Data);
  if (crc != crc0) {
    PrintFailure(crc, crc0);
    return false;
  }
  return true;
} // TestSize

template<class CrcTraits>
bool Test() {
  using namespace std;
  auto saveIo = tjg::SaveIo{cout};
  using Crc = tjg::crc::Known<CrcTraits>;
  cout << "Testing " << Crc::Name;
  Crc crc;
  crc.update(TestBuf);
  if (crc != Crc::Check) {
    PrintFailure(crc, Crc::Check);
    return false;
  }

  if (!TestSize<CrcTraits>())
    return false;

  if (!TestSize<CrcTraits, 127>())
    return false;

  if (!TestSize<CrcTraits, 128>())
    return false;

  if (!TestSize<CrcTraits, 129>())
    return false;

  if (!TestSize<CrcTraits, 129, 5>())
    return false;

  cout << " PASSED" << endl;
  return true;
} // Test

int main() {
  int failCount = 0;

  using Crcs = tjg::crc::test_detail::KnownCrcs;

  using namespace boost::mp11;
  mp_for_each<Crcs>([&](auto I) {
    if (!Test<decltype(I)>())
      ++failCount;
  });

  std::cout << failCount << '/' << mp_size<Crcs>::value
            << " tests failed." << std::endl;
  return (failCount == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
} // main
