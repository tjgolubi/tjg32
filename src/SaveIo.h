#include <iostream>
#include <iomanip>

namespace tjg {

struct SaveIo {
  std::ostream& os;
  char fill;
  std::ios_base::fmtflags flags;
  explicit SaveIo(std::ostream& os_ = std::cout) noexcept
    : os{os_}, fill{os_.fill()}, flags{os_.flags()} { }
  ~SaveIo() noexcept {
    (void) os.fill(fill);
    (void) os.flags(flags);
  }
}; // SaveIo

std::ostream& SetHex(std::ostream& os = std::cout) noexcept
  { return os << std::hex << std::setfill('0'); }

std::ostream& SetDec(std::ostream& os = std::cout) noexcept
  { return os << std::dec << std::setfill(' '); }

} // tjg
