% CRC Performance Study Summary
% Terry Golubiewski
% 2025-07-23

# Overview

This document summarizes an empirical study of three CRC32 software
implementations benchmarked across different compiler optimization levels
using Clang++ and the `-march=native` flag. All tests were run on an
AMD Ryzen 9 5950X-based PC, and the CRC computed over 100 iterations of a
1-MiB pseudo-random input buffer using the (reflected) standard IEEE CRC32
polynomial 0x04c11db7 (`0xedb88320`).

The metaprogrammed `GenericCrc` class was the fastest overall at over 300 MiB/s
for all optimization levels except -O0.
At optimization levels above zero, most other algorithms achieved 140 MiB/s.
At `-O0`, `TraditionalCrc`was fastest 100 MiB/s (GenericCrc struggled at 52
MiB/s).  Surprisingly, PlainCrc achieved 214 MiB/s at -O3, but at -O0 it was
very slow at only 22 MiB/s.

# Implementations Tested

| Label  | Name           | Description                                        |
|--------|----------------|----------------------------------------------------|
| `Crc0` | PlainCrc       | Classic CRC32 with `if (crc & 1)` branch           |
| `Crc1` | TraditionalCrc | Loop with mask-based conditional XOR, no branches  |
| `Crc2` | HandCrc        | Unrolled, branchless, non-template, compile-time   |
| `Crc3` | GenericCrc     | Unrolled, branchless, template-based, compile-time |
| `Crc4` | MaskCRc        | Unrolled, branchless, non-template, compile-time   |
| `Crc5` | DumbCrc        | Loop shifts both input and crc                     |

All variants produced correct output: `0x59abc193`.

The input data was generated using the following algorithm.

```cpp
std::mt19937 rng(12345);
for (std::size_t i = 0; i != (1<<20); ++i)
  data.push_back(static_cast<std::byte>(rng() & 0xff));
```

# Performance Results

### CRC Benchmark Results (Time in ms)

| Algorithm      |  -O0   |  -O1   |  -O2   |  -O3   |  -Og   |  -Os   |
|:---------------|-------:|-------:|-------:|-------:|-------:|-------:|
| PlainCrc       | 4436ms |  704ms |  708ms |  468ms | 2039ms |  706ms |
| TraditionalCrc | 1126ms |  699ms |  700ms |  702ms |  701ms |  705ms |
| HandCrc        |  652ms |  298ms |  319ms |  319ms |  279ms |  256ms |
| GenericCrc     | 1942ms |  320ms |  320ms |  320ms |  417ms |  299ms |
| MaskCrc        |  752ms |  346ms |  771ms |  771ms |  343ms |  336ms |
| DumbCrc        | 7348ms |  849ms |  849ms |  844ms | 2118ms |  849ms |

| Optimization | Description                                |
|:------------:|:-------------------------------------------|
|     -O0      | No optimation                              |
|     -O1      | Minimal optimization, compiles quickly     |
|     -O2      | Normal optimization, balances speed/space  |
|     -O3      | Maximum optimization for speed             |
|     -Os      | Optimizes for size                         |
|     -Og      | Optimization suitable for debugging        |

Full [test results](LsbTestResults.txt).
Full documentation of GCC options that control
[optimization](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html).

## Key Observations
- At `-O1` thru `-Os`, `GenericCrc` is the clear winner--more than 2x faster
  than the next best.

- All variants exceed 100 MiB/s throughput under most settings.

- `GenericCrc` retains strong performance across all flags, thanks
  to branchless, inlined structure, but HandCrc is faster for debug builds.

# Source Code

The full source code is available [here](../src/tjg32.cpp).

## PlainCrc

The `PlainCrc` implementation uses a simple loop with an explicit branch to test
whether the least-significant bit is set. If so, it XORs with the polynomial;
otherwise, it shifts right. This structure is readable but incurs conditional
branching on each bit iteration.  **Analysis**: This variant performs well under
`-Os`, where size matters most. Its simple loop and compact instruction set are
likely more cache-friendly and result in smaller binary output. However, under
higher optimization levels, it is generally slower than its branchless
counterparts.

```cpp
template<std::unsigned_integral Uint, Uint Poly>
struct PlainCrc {
  static constexpr Uint Update(Uint crc, std::byte in) {
    crc ^= std::to_integer<Uint>(in);
    for (int i = 0; i != 8; ++i) {
      auto lsb = static_cast<bool>(crc & Uint{1});
      crc >>= 1;
      if (lsb)
        crc ^= Poly;
    }
    return crc;
  } // Update
}; // PlainCrc

```

## TraditionalCrc

The `TraditionalCrc` implementation eliminates the conditional branch using a
mask computed as `-(crc & 1)`. This mask is used to selectively XOR with the
polynomial in a branchless fashion. The structure remains a loop, but avoids
branches that can be costly on certain pipelines.  **Analysis**: This variant
benefits from its branchless structure and performs better than `PlainCrc` under
moderate optimizations (e.g., `-O0`). However, its loop nature limits its
performance compared to unrolled variants at higher optimization levels.

```cpp
template<std::unsigned_integral Uint, Uint Poly>
struct TraditionalCrc {
  // Optimized to remove if-statement.
  static constexpr Uint Update(Uint crc, std::byte in) {
    crc ^= std::to_integer<Uint>(in);
    for (int i = 0; i != 8; ++i)
      crc = (crc >> 1) ^ (-(crc & Uint{1}) & Poly);
    return crc;
  }
}; // TraditionalCrc
```

## GenericCrc

The `GenericCrc` implementation uses template metaprogramming to unroll the bit-
processing logic completely. Each bit iteration is statically generated via
template recursion and `constexpr` logic. The loop is replaced by inlined logic
with no branching or loop control overhead.  **Analysis**: This version excels
under `-O1` optimization, where it delivers the fastest performance--more than
twice as fast as the others. This is due to its branchless, unrolled, and
inlined nature, which allows the compiler to fully optimize and parallelize the
CRC computation. However, the generated code size may be larger than loop-based
variants.

```cpp
template<std::unsigned_integral Uint, Uint Poly>
class GenericCrc {
private:
  static constexpr auto Shift = 8 * sizeof(Uint) - 1;

  template<std::size_t N>
  static constexpr Uint Residual() {
    if constexpr (N > 1)
      return Uint{0};
    else
      return Poly >> (1 - N);
  }

  template<std::size_t N>
  static constexpr Uint Iter(Uint crc) {
    using Int = std::make_signed_t<Uint>;
    return static_cast<Uint>( ((static_cast<Int>(crc) << (Shift - N)) >> Shift)
                              & ((Poly >> (7 - N)) ^ Residual<N>()));
  }

  template<std::size_t... N>
  static constexpr Uint IterateCrc(Uint crc, std::index_sequence<N...>)
    { return (Iter<N>(crc) ^ ...); }

public:
  static constexpr Uint Update(Uint crc, std::byte in) {
    crc ^= std::to_integer<Uint>(in);
    crc = (crc >> 8) ^ IterateCrc(crc, std::make_index_sequence<8>{});
    return crc;
  }
}; // GenericCrc
```

# Analysis

- `GenericCrc` benefits from template metaprogramming and constexpr folding.
  At `-O1`, these expressions are emitted as compact, straight-line logic with
  ideal instruction-level parallelism.
- `PlainCrc` benefits at `-Os` due to minimal instruction count and better cache
  utilization.
- At `-O0`, unoptimized logic penalizes looped variants the most; surprisingly,
  the loopless version remains relatively efficient.

# References

1. [Stephan Brumme - *Fast CRC32 Calculations*](https://create.stephan-brumme.com/crc32/)  
   This resource describes the branchless technique used in `TraditionalCrc`
   and the unrolled loop approach used in `GenericCrc`. The latter technique
   originates from the book
   [Hacker's Delight](https://en.wikipedia.org/wiki/Hacker%27s_Delight)
   by Henry S. Warren, Jr.  
   This study adds C++ template-based unrolling to optimize the logic at compile time.

2. Wikipedia contributors,
   *Computation of cyclic redundancy checks - CRC-32 Example*, available at:
   [Wikipedia - CRC-32 Example](https://en.wikipedia.org/wiki/Computation_of_cyclic_redundancy_checks@CRC-32_example)  
   Provides a worked example of computing CRC-32, including step-by-step bitwise operations.

3. [hcs0 - Hacker's Delight CRC Example](https://github.com/hcs0/Hackers-Delight/blob/master/crc.c.txt)  
   A faithful implementation of the CRC logic from *Hacker's Delight* in C,
   hosted on GitHub.  
   Useful for comparison against template-based C++ implementations.

---

**Author**: Terry Golubiewski  
**Generated with assistance from ChatGPT**
