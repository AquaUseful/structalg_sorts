#pragma once

#include <algorithm>
#include <bits/iterator_concepts.h>
#include <iterator>
#include <limits>

#include "SortStats.hpp"

template <std::random_access_iterator It>
inline constexpr SortStats direct_insertion_sort(It first, It last) {
  SortStats stats{};

  for (auto i = std::next(first); i != last; std::advance(i, 1)) {
    for (auto j = i; j != first; std::advance(j, -1)) {
      ++stats.comparisons;
      if (*j < *std::prev(j)) {
        ++stats.swaps;
        std::swap(*j, *std::prev(j));
      } else {
        break;
      }
    }
  }

  return stats;
};
