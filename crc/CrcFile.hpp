#include "crc/Crc.hpp"

#include <vector>
#include <fstream>

namespace tjg::crc {

/// Use CRC-32/ISO-HDLC by default.
using DefaultFileCrc = Crc<32, 0x04c11db7, Endian::LsbFirst, 8>;

auto FileCrc(const auto& name, auto crc=DefaultFileCrc{0xffffffff, 0xffffffff})
  -> decltype(crc)::value_type
{
  auto in  = std::ifstream{};
  in.exceptions(std::ios::failbit | std::ios::badbit);
  in.open(name, std::ios::in | std::ios::binary);
  auto buf = std::vector<char>{};
  buf.resize(1<<20);
  for (;;) {
    (void) in.read(buf.data(), std::ssize(buf));
    auto got = static_cast<std::size_t>(in.gcount());
    if (got == 0)
      break;
    crc.update(std::as_bytes(std::span{buf.data(), got}));
  }
  return crc.value();
} // FileCrc

} // tjg::crc
