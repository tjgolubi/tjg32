
#include "CrcTable.h"
#include "SaveIo.h"

#include <iostream>
#include <iomanip>

template<std::integral T, std::size_t N>
void PrintArray(const std::array<T, N>& a) {
  using namespace std;
  auto save = tjg::SaveIo{cout};
  tjg::SetHex(cout);
  constexpr int w = 2 * sizeof(T);
  for (int i = 0; i != ssize(a); ++i) {
    cout << " 0x" << setw(w) << a[i];
    if (i % 8 == 7)
      cout << '\n';
  }
  cout << endl;
} // PrintArray

int main() {
  using namespace tjg;
  // using Table = CrcTable<std::uint32_t, 0x04c11db7, CrcDir::LsbFirst, 0>;
  using Table = CrcTable<std::uint32_t, 0x1edc6f41, CrcDir::LsbFirst, 7>;
  auto tbl = Table::Get();
  PrintArray(tbl);
  return EXIT_SUCCESS;
} // main
