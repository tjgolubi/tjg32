
#include "CrcTable.h"

#include <iostream>
#include <iomanip>

struct SaveIo {
  std::ostream& os;
  char fill;
  std::ios_base::fmtflags flags;
  explicit SaveIo(std::ostream& os_ = std::cout)
    : os{os_}, fill{os_.fill()}, flags{os_.flags()} { }
  ~SaveIo() {
    (void) os.fill(fill);
    (void) os.flags(flags);
  }
}; // SaveIo

std::ostream& SetHex(std::ostream& os = std::cout) noexcept
  { return os << std::hex << std::setfill('0'); }

std::ostream& SetDec(std::ostream& os = std::cout) noexcept
  { return os << std::dec << std::setfill(' '); }

template<std::integral T, std::size_t N>
void PrintArray(const std::array<T, N>& a) {
  using namespace std;
  auto save = SaveIo{cout};
  SetHex(cout);
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
