#include "tjg/bit_reverse.hpp"

#include <cstddef>
#include <cstdint>

namespace tjg {

static_assert(bit_reverse(std::byte{0x00}) == std::byte{0x00});
static_assert(bit_reverse(std::byte{0xff}) == std::byte{0xff});
static_assert(bit_reverse(std::byte{0xa5}) == std::byte{0xa5});
static_assert(bit_reverse(std::byte{0x5a}) == std::byte{0x5a});
static_assert(bit_reverse(std::byte{0xca}) == std::byte{0x53});
static_assert(bit_reverse(std::byte{0x53}) == std::byte{0xca});
static_assert(bit_reverse(std::byte{0x80}) == std::byte{0x01});

static_assert(bit_reverse(uint16_t{0x0000}) == uint16_t{0x0000});
static_assert(bit_reverse(uint16_t{0xffff}) == uint16_t{0xffff});
static_assert(bit_reverse(uint16_t{0xa5ca}) == uint16_t{0x53a5});
static_assert(bit_reverse(uint16_t{0x8001}) == uint16_t{0x8001});
static_assert(bit_reverse(uint16_t{0x0cba}) == uint16_t{0x5d30});
static_assert(bit_reverse(uint16_t{0x4079}) == uint16_t{0x9e02});
static_assert(bit_reverse(uint16_t{0x08fd}) == uint16_t{0xbf10});
static_assert(bit_reverse(uint16_t{0xc522}) == uint16_t{0x44a3});

static_assert(bit_reverse(uint32_t{0x00000000}) == uint32_t{0x00000000});
static_assert(bit_reverse(uint32_t{0xffffffff}) == uint32_t{0xffffffff});
static_assert(bit_reverse(uint32_t{0xa5ca418c}) == uint32_t{0x318253a5});
static_assert(bit_reverse(uint32_t{0x84218421}) == uint32_t{0x84218421});
static_assert(bit_reverse(uint32_t{0xd6db09a4}) == uint32_t{0x2590db6b});
static_assert(bit_reverse(uint32_t{0x8f6c43c5}) == uint32_t{0xa3c236f1});
static_assert(bit_reverse(uint32_t{0xea85be38}) == uint32_t{0x1c7da157});
static_assert(bit_reverse(uint32_t{0xe7f72b2c}) == uint32_t{0x34d4efe7});

static_assert(bit_reverse(uint64_t{0x0000000000000000}) == uint64_t{0x0000000000000000});
static_assert(bit_reverse(uint64_t{0xffffffffffffffff}) == uint64_t{0xffffffffffffffff});
static_assert(bit_reverse(uint64_t{0x124884213579eca8}) == uint64_t{0x15379eac84211248});
static_assert(bit_reverse(uint64_t{0x7826e2e9ea000ed5}) == uint64_t{0xab7000579747641e});
static_assert(bit_reverse(uint64_t{0x3507f3d820833719}) == uint64_t{0x98ecc1041bcfe0ac});
static_assert(bit_reverse(uint64_t{0x0101b43f6d17de8e}) == uint64_t{0x717be8b6fc2d8080});
static_assert(bit_reverse(uint64_t{0x0355ea48d3874068}) == uint64_t{0x1602e1cb1257aac0});
static_assert(bit_reverse(uint64_t{0x6ba0cdcf77cff1c1}) == uint64_t{0x838ff3eef3b305d6});
static_assert(bit_reverse(uint64_t{0x9dbeb90e4f225f0c}) == uint64_t{0x30fa44f2709d7db9});
static_assert(bit_reverse(uint64_t{0xe51717a72902214a}) == uint64_t{0x52844094e5e8e8a7});
static_assert(bit_reverse(uint64_t{0x691f71cbcddb4574}) == uint64_t{0x2ea2dbb3d38ef896});

#if defined(TJG_HAS_INT128X)

static_assert(bit_reverse(uint128_t{0})  == uint128_t{0});
static_assert(bit_reverse(~uint128_t{0}) == ~uint128_t{0});
static_assert(bit_reverse(uint128_t{1})  == uint128_t{1} << 127);
static_assert(bit_reverse(uint128_t{1}<<127) == uint128_t{1});

static_assert(
  []() constexpr {
    constexpr auto a = uint64_t{0x0123456789ABCDEFull};
    constexpr auto b = uint64_t{0x0FEDCBA987654321ull};
    constexpr auto ar = bit_reverse(a);
    constexpr auto br = bit_reverse(b);
    return (bit_reverse(U128(a, b)) == U128(br, ar));
  }()
)

static_assert(
  []() constexpr {
    constexpr auto x = U128(0xDEAD'BEEF'0123'4567ull, 0x89AB'CDEF'7654'3210ull);
    return (bit_reverse(bit_reverse(x)) == x);
  }()
)
#endif

} // tjg


int main() { return 0; }
