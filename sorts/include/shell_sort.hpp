#pragma once

#include <bits/iterator_concepts.h>
#include <cmath>
#include <cstddef>
#include <iterator>

#include "SortStats.hpp"
#include "StrideIterator.hpp"
#include "insertion_sort.hpp"

template <std::bidirectional_iterator It>
inline constexpr SortStats shell_sort(It first, It last) {
  const std::size_t length = std::distance(first, last);
  if (length <= 1) {
    return SortStats{1, 0};
  }
  const std::size_t pass_cout = std::log2(length) - 1;
  std::size_t gap = 1;
  for (auto i{0}; i < pass_cout; ++i) {
    gap = gap * 2 + 1;
  }
  SortStats stats{0, 0};
  for (; gap >= 1; gap = ((gap - 1) / 2)) {
    for (std::size_t gap_shift = 0; gap_shift < gap; ++gap_shift) {
      const StrideIterator stride_first(std::next(first, gap_shift), gap);
      const StrideIterator stride_last =
          make_stride_end_iterator(stride_first, last);
      const SortStats single_stats =
          insertion_sort(stride_first, stride_last);
      stats.comparisons += single_stats.comparisons;
      stats.swaps += single_stats.swaps;
    }
  }
  return stats;
}
