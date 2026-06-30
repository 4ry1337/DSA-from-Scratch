#include "list.h"

#include <gtest/gtest.h>

TEST(List, DefaultConstructorEmpty) {
  dsa::List<int> l;
  EXPECT_TRUE(l.empty());
  EXPECT_EQ(l.size(), 0u);
}

TEST(List, PushBackAndFront) {
  dsa::List<int> l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  EXPECT_EQ(l.size(), 3u);
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 3);
}

TEST(List, PushFront) {
  dsa::List<int> l;
  l.push_front(2);
  l.push_front(1);
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 2);
  EXPECT_EQ(l.size(), 2u);
}

TEST(List, PopFront) {
  dsa::List<int> l;
  l.push_back(1);
  l.push_back(2);
  l.pop_front();
  EXPECT_EQ(l.front(), 2);
  EXPECT_EQ(l.size(), 1u);
}

TEST(List, PopBack) {
  dsa::List<int> l;
  l.push_back(1);
  l.push_back(2);
  l.pop_back();
  EXPECT_EQ(l.back(), 1);
  EXPECT_EQ(l.size(), 1u);
}

TEST(List, Clear) {
  dsa::List<int> l;
  l.push_back(1);
  l.push_back(2);
  l.clear();
  EXPECT_TRUE(l.empty());
  EXPECT_EQ(l.size(), 0u);
}

TEST(List, InsertAtBegin) {
  dsa::List<int> l;
  l.push_back(2);
  l.insert(l.begin(), 1);
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.size(), 2u);
}

TEST(List, InsertAtEnd) {
  dsa::List<int> l;
  l.push_back(1);
  l.insert(l.end(), 2);
  EXPECT_EQ(l.back(), 2);
  EXPECT_EQ(l.size(), 2u);
}

TEST(List, EraseIterator) {
  dsa::List<int> l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  auto it = l.begin();
  ++it;
  l.erase(it);
  EXPECT_EQ(l.size(), 2u);
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 3);
}

TEST(List, EraseRange) {
  dsa::List<int> l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(4);
  auto from = l.begin();
  ++from;
  auto to = l.end();
  --to;
  l.erase(from, to);
  EXPECT_EQ(l.size(), 2u);
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 4);
}

TEST(List, IteratorTraversal) {
  dsa::List<int> l;
  l.push_back(10);  // NOLINT
  l.push_back(20);  // NOLINT
  l.push_back(30);  // NOLINT
  int sum = 0;
  for (int x : l) {
    sum += x;
  }
  EXPECT_EQ(sum, 60);
}

TEST(List, CopyConstructor) {
  dsa::List<int> l;
  l.push_back(1);
  l.push_back(2);
  dsa::List<int> copy = l;
  EXPECT_EQ(copy.size(), 2u);
  copy.push_back(3);
  EXPECT_EQ(l.size(), 2u);
}

TEST(List, MoveConstructor) {
  dsa::List<int> l;
  l.push_back(1);
  l.push_back(2);
  dsa::List<int> moved = std::move(l);
  EXPECT_EQ(moved.size(), 2u);
  EXPECT_EQ(moved.front(), 1);
}

TEST(List, CopyAssignment) {
  dsa::List<int> l;
  l.push_back(5);  // NOLINT
  dsa::List<int> other;
  other = l;
  EXPECT_EQ(other.size(), 1u);
  EXPECT_EQ(other.front(), 5);
}

TEST(List, MoveAssignment) {
  dsa::List<int> l;
  l.push_back(7);  // NOLINT
  dsa::List<int> other;
  other = std::move(l);
  EXPECT_EQ(other.size(), 1u);
  EXPECT_EQ(other.front(), 7);
}

TEST(List, IteratorMismatchThrows) {
  dsa::List<int> a;
  dsa::List<int> b;
  b.push_back(1);
  a.push_back(2);
  auto it = b.begin();
  EXPECT_THROW(a.insert(it, 99), dsa::IteratorMismatchException);
}

TEST(List, PushMoveSemantics) {
  dsa::List<std::string> l;
  std::string s = "hello";
  l.push_back(std::move(s));
  EXPECT_EQ(l.front(), "hello");
}
