#include "bsearch.h"
#include <gtest/gtest.h>

TEST(BinarySearch, FindsElement) {
  std::vector<int> v = {1, 3, 5, 7, 9};
  EXPECT_EQ(dsa::binary_search(v, 5), 2);
}

TEST(BinarySearch, FindFirstElement) {
  std::vector<int> v = {1, 3, 5, 7, 9};
  EXPECT_EQ(dsa::binary_search(v, 1), 0);
}

TEST(BinarySearch, FindLastElement) {
  std::vector<int> v = {1, 3, 5, 7, 9};
  EXPECT_EQ(dsa::binary_search(v, 9), 4);
}

TEST(BinarySearch, ReturnsNulloptWhenMissing) {
  std::vector<int> v = {1, 3, 5};
  EXPECT_FALSE(dsa::binary_search(v, 4).has_value());
}

TEST(BinarySearch, EmptyVector) {
  std::vector<int> v = {};
  EXPECT_FALSE(dsa::binary_search(v, 1).has_value());
}
