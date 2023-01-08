#pragma once

#include <algorithm>
#include <bits/iterator_concepts.h>
#include <concepts>
#include <functional>
#include <iterator>
#include <type_traits>

#include "SortStats.hpp"

template <std::random_access_iterator It>
inline constexpr SortStats internal_sort(It first, It last) {
  std::sort<It>(first, last);
  return SortStats{};
};