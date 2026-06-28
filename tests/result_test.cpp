#include "result.h"
#include <gtest/gtest.h>
#include <string>

TEST(Result, OkIsOk) {
    auto r = dsa::Result<int, std::string>::ok(42); // NOLINT
    EXPECT_TRUE(r.is_ok());
    EXPECT_FALSE(r.is_err());
}

TEST(Result, ErrIsErr) {
    auto r = dsa::Result<int, std::string>::err("fail");
    EXPECT_FALSE(r.is_ok());
    EXPECT_TRUE(r.is_err());
}

TEST(Result, UnwrapOkReturnsValue) {
    auto r = dsa::Result<int, std::string>::ok(7); // NOLINT
    EXPECT_EQ(r.unwrap(), 7);
}

TEST(Result, UnwrapErrThrows) {
    auto r = dsa::Result<int, std::string>::err("oops");
    EXPECT_THROW(r.unwrap(), std::runtime_error);
}

TEST(Result, UnwrapErrReturnsError) {
    auto r = dsa::Result<int, std::string>::err("bad");
    EXPECT_EQ(r.unwrap_err(), "bad");
}

TEST(Result, UnwrapErrOnOkThrows) {
    auto r = dsa::Result<int, std::string>::ok(1);
    EXPECT_THROW(r.unwrap_err(), std::runtime_error);
}

TEST(Result, MapTransformsOk) {
    auto r = dsa::Result<int, std::string>::ok(3);
    auto mapped = r.map([](int x) { return x * 2; });
    ASSERT_TRUE(mapped.is_ok());
    EXPECT_EQ(mapped.unwrap(), 6);
}

TEST(Result, MapPassesThroughErr) {
    auto r = dsa::Result<int, std::string>::err("nope");
    auto mapped = r.map([](int x) { return x * 2; });
    EXPECT_TRUE(mapped.is_err());
    EXPECT_EQ(mapped.unwrap_err(), "nope");
}

TEST(Result, UnwrapOrReturnsValueOnOk) {
    auto r = dsa::Result<int, std::string>::ok(10); // NOLINT
    EXPECT_EQ(r.unwrap_or(99), 10);
}

TEST(Result, UnwrapOrReturnsFallbackOnErr) {
    auto r = dsa::Result<int, std::string>::err("e");
    EXPECT_EQ(r.unwrap_or(99), 99);
}

TEST(Result, UnwrapMutatesValue) {
    auto r = dsa::Result<int, std::string>::ok(5); // NOLINT
    r.unwrap() = 50;                               // NOLINT
    EXPECT_EQ(r.unwrap(), 50);
}
