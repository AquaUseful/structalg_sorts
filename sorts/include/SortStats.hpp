#pragma once

#include <cstddef>

struct SortStats {
  using comparison_count_t = std::size_t;
  using swap_count_t = std::size_t;

  comparison_count_t comparisons{0};
  swap_count_t swaps{0};
};
