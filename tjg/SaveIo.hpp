/// @file
/// @copyright 2025 Terry Golubiewski, all rights reserved.
/// @author Terry Golubiewski
/// Preserve std::ostream state; restore on scope exit.

#pragma once

#include <iostream>
#include <iomanip>

namespace tjg {

/// Preserve std::ostream state; restore on scope exit.
struct SaveIo {
  std::ostream& os;                     ///< Output stream.
  char fill;                            ///< Fill character.
  std::ios_base::fmtflags flags;        ///< Output flags.

  /// Constructor, defaults to std::cout.
  /// @param os_        Output stream.
  explicit SaveIo(std::ostream& os_ = std::cout) noexcept
    : os{os_}, fill{os_.fill()}, flags{os_.flags()} { }

  /// Destructor
  ~SaveIo() noexcept {
    (void) os.fill(fill);
    (void) os.flags(flags);
  }
}; // SaveIo

/// Set std::ostream mode to hexadecimal, fill character to '0'.
/// @param os   Output stream
std::ostream& SetHex(std::ostream& os = std::cout) noexcept
  { return os << std::hex << std::setfill('0'); }

/// Set std::ostream mode to decimal, fill character to ' '.
/// @param os   Output stream
std::ostream& SetDec(std::ostream& os = std::cout) noexcept
  { return os << std::dec << std::setfill(' '); }

} // tjg
