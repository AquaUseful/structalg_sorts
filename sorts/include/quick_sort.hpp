#pragma once

#include "SortStats.hpp"
#include <algorithm>
#include <bits/iterator_concepts.h>
#include <cmath>
#include <iterator>

template <std::random_access_iterator It> struct PartitionResult {
  It iterator;
  SortStats stats;
};

template <std::random_access_iterator It, typename Pred>
inline constexpr PartitionResult<It> partition(It first, It last,
                                               Pred predicate) {
  auto part_start = std::find_if_not(first, last, predicate);

  auto stats = SortStats{static_cast<SortStats::comparison_count_t>(
                             std::distance(first, part_start)),
                         0};
  if (part_start == last) {
    return PartitionResult<It>{part_start, stats};
  }
  for (auto i = std::next(part_start); i != last; ++i) {
    ++stats.comparisons;
    if (predicate(*i)) {
      std::iter_swap(i, part_start);
      ++part_start;
      ++stats.swaps;
    }
  }
  return PartitionResult<It>{part_start, stats};
}

template <std::random_access_iterator It>
inline constexpr SortStats quick_sort(It first, It last) {
  if (std::distance(first, last) <= 1) {
    return SortStats{1, 0};
  }
  const auto pivot = *std::next(first, std::distance(first, last) / 2);
  const auto pred_lt = [&pivot](const auto &el) { return el < pivot; };
  const auto pred_nlt = [&pivot](const auto &el) { return !(el < pivot); };
  PartitionResult<It> part_res1 = partition(first, last, pred_lt);
  PartitionResult<It> part_res2 = partition(part_res1.iterator, last, pred_nlt);
  auto mid1 = part_res1.iterator;
  auto mid2 = part_res2.iterator;
  const SortStats res1 = quick_sort<It>(first, mid1);
  const SortStats res2 = quick_sort<It>(mid2, last);
  const auto res = SortStats{
      part_res1.stats.comparisons + part_res2.stats.comparisons +
          res1.comparisons + res2.comparisons,
      part_res1.stats.swaps + part_res2.stats.swaps + res1.swaps + res2.swaps};
  return res;
}
