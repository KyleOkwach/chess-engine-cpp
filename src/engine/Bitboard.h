#pragma once
#include "Types.h"

inline bool get_bit(uint64_t bb, int square) { return (bb >> square) & 1ULL; }
inline void set_bit(uint64_t& bb, int square) { bb |= (1ULL << square); }
inline void clear_bit(uint64_t& bb, int square) { bb &= ~(1ULL << square); }
