#pragma once

#include <algorithm>
#include <bits/iterator_concepts.h>
#include <iterator>

#include "SortStats.hpp"

template <std::random_access_iterator It>
inline constexpr SortStats selection_sort(It first, It last) {
  SortStats stats{};
  for (auto insert_pos = first; insert_pos != last;
       std::advance(insert_pos, 1)) {

    // From https://en.cppreference.com/w/cpp/algorithm/min_element
    stats.comparisons += std::distance(insert_pos, last) - 1;

    auto mini = std::min_element(insert_pos, last);
    if (mini != insert_pos) {
      ++stats.swaps;
      std::swap(*insert_pos, *mini);
    }
  }
  return stats;
};
