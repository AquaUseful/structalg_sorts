#pragma once

#include <bits/iterator_concepts.h>
#include <concepts>
#include <functional>
#include <iterator>
#include <type_traits>

#include "SortStats.hpp"

template <std::random_access_iterator It>
inline constexpr SortStats direct_swap_sort(It first, It last) {
  SortStats stats{};

  auto last_swap_pos = std::prev(last, 1);

  bool has_swaps;
  do {
    has_swaps = false;
    auto bound = last_swap_pos;
    for (auto i = first; i != bound; std::advance(i, 1)) {
      ++stats.comparisons;
      if (*i > *std::next(i)) {
        ++stats.swaps;
        has_swaps = true;
        last_swap_pos = i;
        std::swap(*i, *std::next(i));
      }
    }
  } while (has_swaps);

  return stats;
};