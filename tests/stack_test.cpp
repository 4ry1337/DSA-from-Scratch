#include "stack.h"
#include <gtest/gtest.h>

TEST(Stack, DefaultConstructorEmpty) {
    dsa::Stack<int> s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
}

TEST(Stack, InitializerList) {
    dsa::Stack s = {1, 2, 3}; // NOLINT
    EXPECT_EQ(s.size(), 3u);
    EXPECT_EQ(s.top(), 3);
}

TEST(Stack, PushIncreasesSize) {
    dsa::Stack<int> s;
    s.push(1);
    s.push(2);
    EXPECT_EQ(s.size(), 2u);
}

TEST(Stack, TopReturnsLast) {
    dsa::Stack<int> s;
    s.push(10); // NOLINT
    s.push(20); // NOLINT
    EXPECT_EQ(s.top(), 20);
}

TEST(Stack, PopDecreasesSize) {
    dsa::Stack<int> s;
    s.push(1);
    s.push(2);
    s.pop();
    EXPECT_EQ(s.size(), 1u);
    EXPECT_EQ(s.top(), 1);
}

TEST(Stack, PushMove) {
    dsa::Stack<std::string> s;
    std::string val = "world";
    s.push(std::move(val));
    EXPECT_EQ(s.top(), "world");
}

TEST(Stack, LifoOrder) {
    dsa::Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(s.top(), 3);
    s.pop();
    EXPECT_EQ(s.top(), 2);
    s.pop();
    EXPECT_EQ(s.top(), 1);
}

TEST(Stack, CopyConstructor) {
    dsa::Stack<int> s;
    s.push(1);
    s.push(2);
    dsa::Stack<int> copy = s;
    EXPECT_EQ(copy.size(), 2u);
    EXPECT_EQ(copy.top(), 2);
    copy.push(3);
    EXPECT_EQ(s.size(), 2u);
}

TEST(Stack, MoveConstructor) {
    dsa::Stack<int> s;
    s.push(5); // NOLINT
    dsa::Stack<int> moved = std::move(s);
    EXPECT_EQ(moved.size(), 1u);
    EXPECT_EQ(moved.top(), 5);
}

TEST(Stack, CopyAssignment) {
    dsa::Stack<int> s;
    s.push(42); // NOLINT
    dsa::Stack<int> other;
    other = s;
    EXPECT_EQ(other.size(), 1u);
    EXPECT_EQ(other.top(), 42);
}

TEST(Stack, MoveAssignment) {
    dsa::Stack<int> s;
    s.push(99); // NOLINT
    dsa::Stack<int> other;
    other = std::move(s);
    EXPECT_EQ(other.size(), 1u);
    EXPECT_EQ(other.top(), 99);
}

/* TEST(Stack, SelfAssignment) {
    dsa::Stack<int> s;
    s.push(1);
    s = s; // NOLINT
    EXPECT_EQ(s.size(), 1u);
} */

TEST(Stack, TopConst) {
    dsa::Stack<int> s;
    s.push(7); // NOLINT
    const dsa::Stack<int> &cs = s;
    EXPECT_EQ(cs.top(), 7);
}
