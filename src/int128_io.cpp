#include <tjg/Integer.hpp>
#include <charconv>
#include <string_view>
#include <ostream>
#include <ios>
#include <concepts>

namespace {

void Emit(std::ostream& os, tjg::uint128_t mag, char sign='\0') {
  using namespace std;

  auto base  = 10;
  auto upper = false;
  switch (os.flags() & ios_base::basefield) {
    case ios_base::hex:
      base  = 16;
      upper = ((os.flags() & ios_base::uppercase) != 0);
      break;
    case ios_base::oct:
      base = 8;
      break;
    default:
      break;
  }

  constexpr auto BufSize = size_t{numeric_limits<tjg::uint128_t>::digits/3 + 3};
  char buf[BufSize];
  auto p = buf;

  if (sign != '\0')
    *p++ = sign;

  if (os.flags() & ios_base::showbase) {
    switch (base) {
      case  8: *p++ = '0'; break;
      case 16: *p++ = '0'; *p++ = (upper ? 'X' : 'x'); break;
      default: break;
    }
  }

  auto r = to_chars(p, buf + BufSize, mag, base);
  if (r.ec != std::errc{})
    throw std::logic_error{"128-bit operator<<: std::to_chars() failed"};

  if (upper) {
    for (auto pp = p; pp < r.ptr; ++pp) {
      char c = *pp;
      if (c >= 'a' && c <= 'f')
        *pp = static_cast<char>(c - 'a' + 'A');
    }
  }

  auto pfx   = string_view{buf, p};
  auto dgt   = string_view{p, r.ptr};
  auto width = static_cast<size_t>(os.width(0));
  auto total = size(pfx) + size(dgt);
  if (total >= width) {
    os.write(data(pfx), ssize(pfx));
    os.write(data(dgt), ssize(dgt));
    return;
  }
  auto pad  = width - total;
  auto fill = os.fill();
  auto adj  = os.flags() & ios_base::adjustfield;
  switch (adj) {
    case ios_base::left:
      os.write(data(pfx), ssize(pfx));
      os.write(data(dgt), ssize(dgt));
      for (size_t i = 0; i < pad; ++i) os.put(fill);
      break;
    case ios_base::internal:
      os.write(data(pfx), ssize(pfx));
      for (size_t i = 0; i < pad; ++i) os.put(fill);
      os.write(data(dgt), ssize(dgt));
      break;
    default:
      for (size_t i = 0; i < pad; ++i) os.put(fill);
      os.write(data(pfx), ssize(pfx));
      os.write(data(dgt), ssize(dgt));
      break;
  }
} // Emit

} // local

std::ostream& operator<<(std::ostream& os, tjg::uint128_t v) {
  Emit(os, v);
  return os;
}

std::ostream& operator<<(std::ostream& os, tjg::int128_t v) {
  if ((os.flags() & std::ios_base::basefield) != std::ios_base::dec) {
    Emit(os, static_cast<tjg::uint128_t>(v));
    return os;
  }
  auto neg  = (v < 0);
  auto mag  = static_cast<tjg::uint128_t>(neg ? -v : v);
  auto sign = '\0';
  if (neg || (os.flags() & std::ios_base::showpos))
    sign = neg ? '-' : '+';
  Emit(os, mag, sign);
  return os;
}
