#include "vector.h"
#include <iostream>

int main() {
  dsa::Vector<int> vec{};
  for (int i{}; i < 100; i++) {
    vec.push_back(i);
  }

  std::cout << vec.size() << std::endl;
  std::cout << vec.capacity() << std::endl;
  std::cout << vec.back() << std::endl;

  for (auto iter = vec.begin(); iter != vec.end(); iter++) {
    std::cout << *iter << ", ";
  }
  std::cout << std::endl;

  return 0;
}
