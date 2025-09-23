#include <tjg/Integer.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <limits>
#include <iomanip>
#include <charconv>

using tjg::uint128_t;
using tjg::int128_t;

static_assert(to_string(uint128_t{1234}) == "1234");
static_assert(to_string(int128_t{-1234}) == "-1234");

namespace {

constexpr uint128_t MakeU128(std::uint64_t hi, std::uint64_t lo) noexcept
  { return tjg::U128(hi, lo); }

template<class T, class F>
std::string Render(const T& v, F fmt) {
  std::ostringstream os;
  fmt(os);
  os << v;
  return os.str();
}

} // local

// ---------- Unsigned: hex/dec/oct, prefixes, uppercase ----------------

TEST(Uint128Stream, HexLower_NoShowbase) {
  uint128_t v = MakeU128(0, 0x1A2Bu);
  auto s = Render(v, [](std::ostringstream& os) {
    os << std::hex;
  });
  EXPECT_EQ(s, "1a2b");
}

TEST(Uint128Stream, HexUpper_Showbase) {
  uint128_t v = MakeU128(0, 0xDEADBEEFCAFEBABEull);
  auto s = Render(v, [](std::ostringstream& os) {
    os << std::hex << std::showbase << std::uppercase;
  });
  EXPECT_EQ(s, "0XDEADBEEFCAFEBABE");
}

TEST(Uint128Stream, Oct_Showbase) {
  uint128_t v = MakeU128(0, 012345670123ull);  // oct literal
  auto s = Render(v, [](std::ostringstream& os) {
    os << std::oct << std::showbase;
  });
  // Expect single leading '0' plus digits (no extra '0o' in iostreams)
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s[0], '0');
}

// ---------- Unsigned: width/fill/alignment ----------------------------

TEST(Uint128Stream, Width_Right_Default) {
  uint128_t v = MakeU128(0, 0xBEEFull);
  auto s = Render(v, [](std::ostringstream& os) {
    os << std::hex << std::showbase << std::setw(12) << std::setfill('0');
  });
  // Right pad (default): width 12, prefix included.
  // "0x" + "beef" = 6 chars → need 6 leading '0's.
  EXPECT_EQ(s, "0000000xbeef");
}

TEST(Uint128Stream, Width_Left) {
  uint128_t v = MakeU128(0, 0xBEEFull);
  auto s = Render(v, [](std::ostringstream& os) {
    os << std::hex << std::left << std::showbase
       << std::setw(12) << std::setfill('_');
  });
  // "0x" + "beef" = 6 chars, then 6 underscores on the right.
  EXPECT_EQ(s, "0xbeef______");
}

TEST(Uint128Stream, Width_Internal) {
  uint128_t v = MakeU128(0, 0x1234ull);
  auto s = Render(v, [](std::ostringstream& os) {
    os << std::hex << std::internal << std::showbase
       << std::setw(10) << std::setfill('0');
  });
  // internal: prefix first, then pad, then digits → "0x" + "0000" + "1234"
  EXPECT_EQ(s, "0x00001234");
}

// ---------- Unsigned: zero and large values ---------------------------

TEST(Uint128Stream, Zero_AllBases) {
  uint128_t v = 0;
  {
    auto s = Render(v, [](std::ostringstream& os) { os << std::dec; });
    EXPECT_EQ(s, "0");
  }
  {
    auto s = Render(v, [](std::ostringstream& os) { os << std::hex; });
    EXPECT_EQ(s, "0");
  }
  {
    auto s = Render(v, [](std::ostringstream& os) { os << std::oct; });
    EXPECT_EQ(s, "0");
  }
}

TEST(Uint128Stream, Large_HexUpper_Showbase) {
  // 0xFFFF'FFFF'FFFF'FFFF'0000'0000'0000'0001
  uint128_t v = MakeU128(0xFFFF'FFFF'FFFF'FFFFull, 0x0000'0000'0000'0001ull);
  auto s = Render(v, [](std::ostringstream& os) {
    os << std::hex << std::uppercase << std::showbase;
  });
  EXPECT_EQ(s, "0XFFFFFFFFFFFFFFFF0000000000000001");
}

TEST(Uint128Stream, Negative_Hex_PrefixAfterSign) {
  uint128_t v = static_cast<uint128_t>(-0x1234);
  auto s = Render(v, [](std::ostringstream& os) {
    os << std::hex << std::showbase;
  });
  EXPECT_EQ(s, "0xffffffffffffffffffffffffffffedcc");
}

// ---------- Signed: sign handling, showpos, hex/oct semantics ---------

TEST(Int128Stream, Negative_Dec) {
  int128_t v = static_cast<int128_t>(-123456789012345678LL);
  auto s = Render(v, [](std::ostringstream& os) {
    os << std::dec;
  });
  EXPECT_EQ(s, "-123456789012345678");
}

TEST(Int128Stream, Positive_Showpos_Dec) {
  int128_t v = static_cast<int128_t>(987654321);
  auto s = Render(v, [](std::ostringstream& os) {
    os << std::dec << std::showpos;
  });
  EXPECT_EQ(s, "+987654321");
}

TEST(Int128Stream, Negative_Hex_TwosComplement_NoSign) {
  // For hex/oct, standard iostreams print as unsigned (two's complement).
  int128_t v = static_cast<int128_t>(-0x1234);
  auto s = Render(v, [](std::ostringstream& os) {
    os << std::hex << std::showbase;
  });
  EXPECT_EQ(s, "0xffffffffffffffffffffffffffffedcc");
}

TEST(Int128Stream, Showpos_IgnoredInHex) {
  int128_t v = static_cast<int128_t>(0x2A);
  auto s = Render(v, [](std::ostringstream& os) {
    os << std::hex << std::showpos << std::showbase;
  });
  EXPECT_EQ(s, "0x2a");  // no '+'
}

TEST(Int128Stream, Showpos_IgnoredInOct) {
  int128_t v = static_cast<int128_t>(042);  // octal 34
  auto s = Render(v, [](std::ostringstream& os) {
    os << std::oct << std::showpos << std::showbase;
  });
  EXPECT_EQ(s, "042");   // no '+', single leading '0'
}

TEST(Int128Stream, Internal_Padding_WithPrefix_NoSign) {
  // showpos is ignored in hex; width 12 → pad 6 zeros after "0x".
  int128_t v = static_cast<int128_t>(0x1ABCull);
  auto s = Render(v, [](std::ostringstream& os) {
    os << std::hex << std::showbase << std::showpos
       << std::internal << std::setw(12) << std::setfill('0');
  });
  EXPECT_EQ(s, "0x0000001abc");
}

TEST(Int128Stream, Uppercase_AffectsHexAndPrefix) {
  int128_t v = static_cast<int128_t>(0xABCD);
  auto s = Render(v, [](std::ostringstream& os) {
    os << std::hex << std::uppercase << std::showbase;
  });
  EXPECT_EQ(s, "0XABCD");
}

TEST(ToString, U128ToString) {
  auto v = static_cast<uint128_t>(1234);
  EXPECT_EQ(to_string(v), "1234");
}

TEST(ToString, I128ToString) {
  auto v = static_cast<int128_t>(-7890);
  EXPECT_EQ(to_string(v), "-7890");
}

TEST(ToString, I128Min) {
  const auto v = std::numeric_limits<int128_t>::min();
  const auto s = to_string(v);
  const auto l = s.size();
  char buf[128];
  const auto end = buf + 128;
  const auto r = std::to_chars(buf, end, v);
  const auto t = std::string_view{buf, r.ptr};
  EXPECT_EQ(r.ec, std::errc{});
  EXPECT_EQ(r.ptr, (buf + l));
  EXPECT_EQ(s, t);
}

TEST(ToString, I128Max) {
  const auto v = std::numeric_limits<int128_t>::max();
  const auto s = to_string(v);
  const auto l = s.size();
  char buf[128];
  const auto end = buf + 128;
  const auto r = std::to_chars(buf, end, v);
  const auto t = std::string_view{buf, r.ptr};
  EXPECT_EQ(r.ec, std::errc{});
  EXPECT_EQ(r.ptr, (buf + l));
  EXPECT_EQ(s, t);
}

TEST(ToString, U128Min) {
  const auto v = std::numeric_limits<uint128_t>::min();
  const auto s = to_string(v);
  const auto l = s.size();
  char buf[128];
  const auto end = buf + 128;
  const auto r = std::to_chars(buf, end, v);
  const auto t = std::string_view{buf, r.ptr};
  EXPECT_EQ(r.ec, std::errc{});
  EXPECT_EQ(r.ptr, (buf + l));
  EXPECT_EQ(s, t);
}

TEST(ToString, U128Max) {
  const auto v = std::numeric_limits<uint128_t>::max();
  const auto s = to_string(v);
  const auto l = s.size();
  char buf[128];
  const auto end = buf + 128;
  const auto r = std::to_chars(buf, end, v);
  const auto t = std::string_view{buf, r.ptr};
  EXPECT_EQ(r.ec, std::errc{});
  EXPECT_EQ(r.ptr, (buf + l));
  EXPECT_EQ(s, t);
}
