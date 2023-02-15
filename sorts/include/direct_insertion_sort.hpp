#pragma once

#include <algorithm>
#include <bits/iterator_concepts.h>
#include <functional>
#include <iterator>
#include <limits>

#include "SortStats.hpp"

template <std::forward_iterator It>
inline constexpr It upper_bound(It first, It last,
                                const typename It::reference val) {
  for (auto i = first; i < last; std::advance(i, 1)) {
    if (*i > val) {
      return i;
    }
  }
}

template <std::random_access_iterator It>
inline constexpr SortStats direct_insertion_sort(It first, It last) {
  SortStats stats{};
  // В начале считаем, что отсортирован только 1 элменент
  It sorted_end = std::next(first);
  // Пока весь массив не отсортирован...
  while (sorted_end <= last) {
    stats.comparisons += 2;
    // Если элемент после отсортированного куска не на своем месте...
    if (*std::prev(sorted_end) > *sorted_end) {
      // Запоминаем элемент для вставки
      const auto element_to_move = *sorted_end;
      // Ищем место для вставки (элемент, который больше вставляемого)
      const auto insert_position =
          upper_bound(first, sorted_end, element_to_move);
      stats.comparisons += std::distance(first, insert_position);
      // Сдвигаем всю последовтельность на 1 вправо для освобождения места
      std::shift_right(insert_position, std::next(sorted_end), 1);
      stats.swaps += std::distance(insert_position, std::next(sorted_end)) - 1;
      // Вставляем элемент на свое место
      *insert_position = element_to_move;
      stats.swaps += 2;
    }
    std::advance(sorted_end, 1);
  }
  return stats;
};
