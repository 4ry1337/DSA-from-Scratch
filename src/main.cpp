#include "bsearch.h"
#include <iostream>
#include <vector>

int main() {
  std::vector<int> vec = {0, 1, 2, 3, 4, 12, 13, 14};
  auto result = dsa::binary_search(vec, 42);
  if (result.has_value()) {
    std::cout << result.value() << std::endl;
  } else {
    std::cout << "NOT FOUND" << std::endl;
  }
  return 0;
}
