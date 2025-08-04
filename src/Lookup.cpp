
#include "CrcTable.h"
#include "SaveIo.h"
#include "Integer.h"

#include <iostream>
#include <iomanip>

template<std::integral T, std::size_t N>
void PrintArray(const std::array<T, N>& a) {
  using namespace std;
  auto save = tjg::SaveIo{cout};
  tjg::SetHex(cout);
  constexpr int w = 2 * sizeof(T);
  int cols = 80 / (w+1);
  for (int i = 16; i != 1; i /= 2) {
    if (i <= cols) {
      cols = i;
      break;
    }
  }
  for (int i = 0; i != ssize(a); ++i) {
    cout << " " << setw(w) << static_cast<std::uint64_t>(a[i]);
    if (i % cols == cols-1)
      cout << '\n';
  }
  cout << endl;
} // PrintArray

int main() {
  using namespace tjg;
  static constexpr auto Dir = CrcDir::LsbFirst;
  static constexpr std::size_t Bits = 64;
  using Uint = tjg::uint_t<Bits>::least;
  static constexpr Uint Poly = 0xad93d23594c935a9;
  static constexpr auto XPoly = (Dir==CrcDir::MsbFirst) ? Poly : Reflect(Poly);
  SetHex();
  int w = 2 * sizeof(XPoly);
  std::cout <<  "Poly = 0x"  << std::setw(w) << Poly
            << " XPoly = 0x" << std::setw(w) << XPoly << std::endl;
  SetDec();
  using Table0 = CrcTable<Uint, XPoly, Dir, 0>;
  using Table1 = CrcTable<Uint, XPoly, Dir, 1>;
  using Table2 = CrcTable<Uint, XPoly, Dir, 2>;
  using Table3 = CrcTable<Uint, XPoly, Dir, 3>;
  using Table4 = CrcTable<Uint, XPoly, Dir, 4>;
  using Table5 = CrcTable<Uint, XPoly, Dir, 5>;
  using Table6 = CrcTable<Uint, XPoly, Dir, 6>;
  using Table7 = CrcTable<Uint, XPoly, Dir, 7>;
  auto tbl0 = Table0::Get();
  auto tbl1 = Table1::Get();
  auto tbl2 = Table2::Get();
  auto tbl3 = Table3::Get();
  auto tbl4 = Table4::Get();
  auto tbl5 = Table5::Get();
  auto tbl6 = Table6::Get();
  auto tbl7 = Table7::Get();
  PrintArray(tbl0);
  PrintArray(tbl1);
  PrintArray(tbl2);
  PrintArray(tbl3);
  PrintArray(tbl4);
  PrintArray(tbl5);
  PrintArray(tbl6);
  PrintArray(tbl7);
  return EXIT_SUCCESS;
} // main
