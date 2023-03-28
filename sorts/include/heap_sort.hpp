#pragma once

#include "SortStats.hpp"
#include <algorithm>
#include <bits/iterator_concepts.h>
#include <iterator>

template <std::random_access_iterator It>
SortStats balance_down(It first, It last, It pos) {
  It left = first + std::distance(first, pos) * 2 + 1;
  It right = first + std::distance(first, pos) * 2 + 2;
  It max = pos;
  if ((left < last) && (*left > *max)) {
    max = left;
  }
  if ((right < last) && (*right > *max)) {
    max = right;
  }
  if (max != pos) {
    std::iter_swap(max, pos);
    SortStats rres = balance_down(first, last, max);
    return SortStats{rres.comparisons + 2, rres.swaps + 1};
  }
  return SortStats{2, 0};
}

template <std::random_access_iterator It>
SortStats make_heap(It first, It last) {
  SortStats stats{};
  for (It pos = first + std::distance(first, last) / 2; pos >= first; --pos) {
    const SortStats bstats = balance_down(first, last, pos);
    stats.comparisons += bstats.comparisons;
    stats.swaps += bstats.swaps;
  }
  return stats;
}

template <std::random_access_iterator It>
SortStats heap_sort(It first, It last) {
  SortStats stats = make_heap(first, last);
  while (last > first) {
    --last;
    std::iter_swap(first, last);
    const SortStats bstats = balance_down(first, last, first);
    stats.swaps += bstats.swaps;
    stats.comparisons += bstats.comparisons;
  }
  return stats;
}
