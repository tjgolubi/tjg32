#include "crc/Crc.hpp"

#include <vector>
#include <fstream>

namespace tjg::crc {

namespace detail {

template<class T>
concept CrcLike = requires { typename T::value_type; }
               && requires(T x, std::span<const std::byte> s) {
                    x.reset();
                    x.update(s);
                    x.value();
                  };

} // detail

/// Use CRC-32/ISO-HDLC by default.
using DefaultFileCrc = Crc<32, 0x04c11db7, Endian::LsbFirst, 8>;

auto FileCrc(const auto& name, auto crc)
requires detail::CrcLike<decltype(crc)>
{
  crc.reset();
  auto in = std::ifstream{};
  in.exceptions(std::ios::failbit | std::ios::badbit);
  in.open(name, std::ios::in | std::ios::binary);
  in.exceptions(std::ios::badbit);
  auto buf = std::vector<char>{};
  buf.resize(1<<20);
  while (!in.eof()) {
    in.clear();
    in.read(buf.data(), std::ssize(buf));
    auto got = static_cast<std::size_t>(in.gcount());
    crc.update(std::as_bytes(std::span{buf.data(), got}));
  }
  in.clear();
  in.exceptions(std::ios::failbit | std::ios::badbit);
  in.close();
  return crc.value();
} // FileCrc

inline auto FileCrc(const auto& name)
{ return FileCrc(name, DefaultFileCrc{0xffffffff, 0xffffffff}); }

} // tjg::crc
