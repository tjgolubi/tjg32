#include "crc/CrcKnown.hpp"

#include <vector>
#include <fstream>
#include <filesystem>

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

auto FileCrc(const auto& name, detail::CrcLike auto crc) {
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
  return crc;
} // FileCrc

inline auto FileCrc(const auto& name)
{ return FileCrc(name, Known<Crc32IsoHdlc, 8>{}); }

inline auto FileCksum(const auto& name) {
  auto crc = FileCrc(name, Known<Crc32Cksum, 8>{});
  auto size = std::filesystem::file_size(name);
  while (size != 0) {
    crc.update(static_cast<std::byte>(size & 0xff));
    size >>= 8;
  }
  return crc;
}

} // tjg::crc
