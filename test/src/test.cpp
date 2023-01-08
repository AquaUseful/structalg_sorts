#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <vector>

#include "direct_insertion_sort.hpp"
#include "direct_selection_sort.hpp"
#include "direct_swap_sort.hpp"

int main() {
  std::vector<int> vec{10, 199, 78, 8, 6, 5};

  const auto res = direct_selection_sort(vec.begin(), vec.end());

  for (const auto &i : vec) {
    std::cout << i << ' ';
  }
  std::cout << '\n' << res.comparisons << ' ' << res.swaps << '\n';

  return EXIT_SUCCESS;
}