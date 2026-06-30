#include "bsearch.h"

#include <gtest/gtest.h>

TEST(BinarySearch, FindsElement) {
  dsa::Vector v = {1, 3, 5, 7, 9};         // NOLINT
  auto result = dsa::binary_search(v, 5);  // NOLINT
  ASSERT_TRUE(result.is_ok());
  EXPECT_EQ(result.unwrap(), 2);
}

TEST(BinarySearch, FindFirstElement) {
  dsa::Vector v = {1, 3, 5, 7, 9};         // NOLINT
  auto result = dsa::binary_search(v, 1);  // NOLINT
  ASSERT_TRUE(result.is_ok());
  EXPECT_EQ(result.unwrap(), 0);
}

TEST(BinarySearch, FindLastElement) {
  dsa::Vector v = {1, 3, 5, 7, 9};         // NOLINT
  auto result = dsa::binary_search(v, 9);  // NOLINT
  ASSERT_TRUE(result.is_ok());
  EXPECT_EQ(result.unwrap(), 4);
}

TEST(BinarySearch, ReturnsErrWhenMissing) {
  dsa::Vector v = {1, 3, 5, 7, 9};  // NOLINT
  EXPECT_TRUE(dsa::binary_search(v, 4).is_err());
}

TEST(BinarySearch, EmptyVector) {
  dsa::Vector<int> v;
  EXPECT_TRUE(dsa::binary_search(v, 1).is_err());
}
