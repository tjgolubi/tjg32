#include "tjg/Reflect.hpp"

#include <cstddef>
#include <cstdint>

namespace IntMath = tjg::IntMath;

static_assert(IntMath::Reflect(std::byte{0x00}) == std::byte{0x00});
static_assert(IntMath::Reflect(std::byte{0xff}) == std::byte{0xff});
static_assert(IntMath::Reflect(std::byte{0xa5}) == std::byte{0xa5});
static_assert(IntMath::Reflect(std::byte{0x5a}) == std::byte{0x5a});
static_assert(IntMath::Reflect(std::byte{0xca}) == std::byte{0x53});
static_assert(IntMath::Reflect(std::byte{0x53}) == std::byte{0xca});
static_assert(IntMath::Reflect(std::byte{0x80}) == std::byte{0x01});

static_assert(IntMath::Reflect(std::uint16_t{0x0000}) == std::uint16_t{0x0000});
static_assert(IntMath::Reflect(std::uint16_t{0xffff}) == std::uint16_t{0xffff});
static_assert(IntMath::Reflect(std::uint16_t{0xa5ca}) == std::uint16_t{0x53a5});
static_assert(IntMath::Reflect(std::uint16_t{0x8001}) == std::uint16_t{0x8001});
static_assert(IntMath::Reflect(std::uint16_t{0x0cba}) == std::uint16_t{0x5d30});
static_assert(IntMath::Reflect(std::uint16_t{0x4079}) == std::uint16_t{0x9e02});
static_assert(IntMath::Reflect(std::uint16_t{0x08fd}) == std::uint16_t{0xbf10});
static_assert(IntMath::Reflect(std::uint16_t{0xc522}) == std::uint16_t{0x44a3});

static_assert(IntMath::Reflect(std::uint32_t{0x00000000}) == std::uint32_t{0x00000000});
static_assert(IntMath::Reflect(std::uint32_t{0xffffffff}) == std::uint32_t{0xffffffff});
static_assert(IntMath::Reflect(std::uint32_t{0xa5ca418c}) == std::uint32_t{0x318253a5});
static_assert(IntMath::Reflect(std::uint32_t{0x84218421}) == std::uint32_t{0x84218421});
static_assert(IntMath::Reflect(std::uint32_t{0xd6db09a4}) == std::uint32_t{0x2590db6b});
static_assert(IntMath::Reflect(std::uint32_t{0x8f6c43c5}) == std::uint32_t{0xa3c236f1});
static_assert(IntMath::Reflect(std::uint32_t{0xea85be38}) == std::uint32_t{0x1c7da157});
static_assert(IntMath::Reflect(std::uint32_t{0xe7f72b2c}) == std::uint32_t{0x34d4efe7});

static_assert(IntMath::Reflect(std::uint64_t{0x0000000000000000}) == std::uint64_t{0x0000000000000000});
static_assert(IntMath::Reflect(std::uint64_t{0xffffffffffffffff}) == std::uint64_t{0xffffffffffffffff});
static_assert(IntMath::Reflect(std::uint64_t{0x124884213579eca8}) == std::uint64_t{0x15379eac84211248});
static_assert(IntMath::Reflect(std::uint64_t{0x7826e2e9ea000ed5}) == std::uint64_t{0xab7000579747641e});
static_assert(IntMath::Reflect(std::uint64_t{0x3507f3d820833719}) == std::uint64_t{0x98ecc1041bcfe0ac});
static_assert(IntMath::Reflect(std::uint64_t{0x0101b43f6d17de8e}) == std::uint64_t{0x717be8b6fc2d8080});
static_assert(IntMath::Reflect(std::uint64_t{0x0355ea48d3874068}) == std::uint64_t{0x1602e1cb1257aac0});
static_assert(IntMath::Reflect(std::uint64_t{0x6ba0cdcf77cff1c1}) == std::uint64_t{0x838ff3eef3b305d6});
static_assert(IntMath::Reflect(std::uint64_t{0x9dbeb90e4f225f0c}) == std::uint64_t{0x30fa44f2709d7db9});
static_assert(IntMath::Reflect(std::uint64_t{0xe51717a72902214a}) == std::uint64_t{0x52844094e5e8e8a7});
static_assert(IntMath::Reflect(std::uint64_t{0x691f71cbcddb4574}) == std::uint64_t{0x2ea2dbb3d38ef896});

int main() { return 0; }
