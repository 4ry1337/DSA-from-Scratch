#include "deque.h"
#include <gtest/gtest.h>

TEST(Deque, DefaultConstructorEmpty) {
    dsa::Deque<int> d;
    EXPECT_TRUE(d.empty());
    EXPECT_EQ(d.size(), 0u);
}

TEST(Deque, InitializerList) {
    dsa::Deque d = {1, 2, 3}; // NOLINT
    EXPECT_EQ(d.size(), 3u);
    EXPECT_FALSE(d.empty());
}

TEST(Deque, EnqueueIncreasesSize) {
    dsa::Deque<int> d;
    d.enqueue(1);
    d.enqueue(2);
    EXPECT_EQ(d.size(), 2u);
}

TEST(Deque, DequeueReturnsFront) {
    dsa::Deque<int> d;
    d.enqueue(10); // NOLINT
    d.enqueue(20); // NOLINT
    EXPECT_EQ(d.dequeue(), 10);
    EXPECT_EQ(d.size(), 1u);
}

TEST(Deque, FifoOrder) {
    dsa::Deque<int> d;
    d.enqueue(1);
    d.enqueue(2);
    d.enqueue(3);
    EXPECT_EQ(d.dequeue(), 1);
    EXPECT_EQ(d.dequeue(), 2);
    EXPECT_EQ(d.dequeue(), 3);
    EXPECT_TRUE(d.empty());
}

TEST(Deque, RandomAccess) {
    dsa::Deque d = {10, 20, 30}; // NOLINT
    EXPECT_EQ(d[0], 10);
    EXPECT_EQ(d[1], 20);
    EXPECT_EQ(d[2], 30);
}

TEST(Deque, RandomAccessConst) {
    const dsa::Deque d = {5, 6, 7}; // NOLINT
    EXPECT_EQ(d[0], 5);
    EXPECT_EQ(d[2], 7);
}

TEST(Deque, CrossChunkEnqueue) {
    dsa::Deque<int> d;
    for (int i = 0; i < 20; ++i) // NOLINT
        d.enqueue(i);
    EXPECT_EQ(d.size(), 20u);
    EXPECT_EQ(d[0], 0);
    EXPECT_EQ(d[16], 16); // NOLINT
    EXPECT_EQ(d[19], 19); // NOLINT
}

TEST(Deque, CrossChunkDequeue) {
    dsa::Deque<int> d;
    for (int i = 0; i < 20; ++i) // NOLINT
        d.enqueue(i);
    for (int i = 0; i < 20; ++i) // NOLINT
        EXPECT_EQ(d.dequeue(), i);
    EXPECT_TRUE(d.empty());
}

TEST(Deque, EnqueueMove) {
    dsa::Deque<std::string> d;
    std::string val = "hello";
    d.enqueue(std::move(val));
    EXPECT_EQ(d[0], "hello");
}

TEST(Deque, CopyConstructor) {
    dsa::Deque<int> d;
    d.enqueue(1);
    d.enqueue(2);
    dsa::Deque<int> copy = d;
    EXPECT_EQ(copy.size(), 2u);
    copy.enqueue(3);
    EXPECT_EQ(d.size(), 2u);
}

TEST(Deque, MoveConstructor) {
    dsa::Deque<int> d;
    d.enqueue(42); // NOLINT
    dsa::Deque<int> moved = std::move(d);
    EXPECT_EQ(moved.size(), 1u);
    EXPECT_EQ(moved.dequeue(), 42);
}

TEST(Deque, CopyAssignment) {
    dsa::Deque<int> d;
    d.enqueue(7); // NOLINT
    dsa::Deque<int> other;
    other = d;
    EXPECT_EQ(other.size(), 1u);
    EXPECT_EQ(other[0], 7);
}

TEST(Deque, MoveAssignment) {
    dsa::Deque<int> d;
    d.enqueue(99); // NOLINT
    dsa::Deque<int> other;
    other = std::move(d);
    EXPECT_EQ(other.size(), 1u);
    EXPECT_EQ(other.dequeue(), 99);
}
