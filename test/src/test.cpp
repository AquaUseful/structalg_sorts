#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <vector>

#include "insertion_sort.hpp"
#include "selection_sort.hpp"
#include "swap_sort.hpp"

int main() {
  std::vector<int> vec{10, 199, 78, 8, 6, 5};

  const auto res = selection_sort(vec.begin(), vec.end());

  for (const auto &i : vec) {
    std::cout << i << ' ';
  }
  std::cout << '\n' << res.comparisons << ' ' << res.swaps << '\n';

  return EXIT_SUCCESS;
}