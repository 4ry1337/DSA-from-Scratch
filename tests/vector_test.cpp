#include "vector.h"
#include <gtest/gtest.h>

TEST(Vector, DefaultConstructorEmpty) {
    dsa::Vector<int> v;
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), 16u);
}

TEST(Vector, InitializerList) {
    dsa::Vector v = {1, 2, 3}; // NOLINT
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(Vector, PushBackIncreasesSize) {
    dsa::Vector<int> v;
    v.push_back(10); // NOLINT
    v.push_back(20); // NOLINT
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
}

TEST(Vector, PushBackMove) {
    dsa::Vector<std::string> v;
    std::string s = "hello";
    v.push_back(std::move(s));
    EXPECT_EQ(v[0], "hello");
    EXPECT_EQ(v.size(), 1u);
}

TEST(Vector, PopBackDecreasesSize) {
    dsa::Vector v = {1, 2, 3}; // NOLINT
    v.pop_back();
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v.back(), 2);
}

TEST(Vector, FrontAndBack) {
    dsa::Vector v = {10, 20, 30}; // NOLINT
    EXPECT_EQ(v.front(), 10);
    EXPECT_EQ(v.back(), 30);
}

TEST(Vector, ReserveGrowsCapacity) {
    dsa::Vector<int> v;
    v.reserve(100); // NOLINT
    EXPECT_GE(v.capacity(), 100u);
    EXPECT_EQ(v.size(), 0u);
}

TEST(Vector, ReserveNoShrink) {
    dsa::Vector<int> v;
    std::size_t cap = v.capacity();
    v.reserve(1);
    EXPECT_EQ(v.capacity(), cap);
}

TEST(Vector, ResizeGrows) {
    dsa::Vector<int> v;
    v.resize(5); // NOLINT
    EXPECT_EQ(v.size(), 5u);
}

TEST(Vector, GrowthOnPushBack) {
    dsa::Vector<int> v;
    std::size_t initial_cap = v.capacity();
    for (std::size_t i = 0; i <= initial_cap; ++i) {
        v.push_back(static_cast<int>(i));
    }
    EXPECT_GT(v.capacity(), initial_cap);
    EXPECT_EQ(v.size(), initial_cap + 1);
}

TEST(Vector, CopyConstructor) {
    dsa::Vector v = {1, 2, 3}; // NOLINT
    dsa::Vector copy = v;      // NOLINT
    EXPECT_EQ(copy.size(), 3u);
    copy.push_back(4);
    EXPECT_EQ(v.size(), 3u);
}

TEST(Vector, MoveConstructor) {
    dsa::Vector v = {1, 2, 3};        // NOLINT
    dsa::Vector moved = std::move(v); // NOLINT
    EXPECT_EQ(moved.size(), 3u);
    EXPECT_EQ(moved[0], 1);
}

TEST(Vector, CopyAssignment) {
    dsa::Vector v = {1, 2}; // NOLINT
    dsa::Vector<int> other;
    other = v;
    EXPECT_EQ(other.size(), 2u);
    EXPECT_EQ(other[0], 1);
}

TEST(Vector, MoveAssignment) {
    dsa::Vector v = {5, 6, 7}; // NOLINT
    dsa::Vector<int> other;
    other = std::move(v);
    EXPECT_EQ(other.size(), 3u);
    EXPECT_EQ(other[2], 7);
}

TEST(Vector, IteratorRange) {
    dsa::Vector v = {1, 2, 3}; // NOLINT
    int sum = 0;
    for (int x : v) {
        sum += x;
    }
    EXPECT_EQ(sum, 6);
}

/* TEST(Vector, SelfAssignment) {
    dsa::Vector v = {1, 2, 3}; // NOLINT
    v = v;                     // NOLINT
    EXPECT_EQ(v.size(), 3u);
} */
