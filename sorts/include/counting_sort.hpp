#pragma once

#include "SortStats.hpp"
#include <algorithm>
#include <bits/iterator_concepts.h>
#include <cstddef>
#include <iterator>
#include <vector>

template <std::forward_iterator It>
inline constexpr SortStats counting_sort(It first, It last) {
  const auto [min, max] = std::minmax_element(first, last);
  const std::size_t counters_count = *max - *min + 1;
  std::vector<std::size_t> counters(counters_count);
  for (auto i = first; i < last; std::advance(i, 1)) {
    ++(*std::next(counters.begin(), *i - *min));
  }
  auto fill_pos = first;
  for (auto i = counters.cbegin(); i < counters.cend(); std::advance(i, 1)) {
    fill_pos =
        std::fill_n(fill_pos, *i, *min + std::distance(counters.cbegin(), i));
  }
  return SortStats{};
}
