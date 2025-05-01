#include <limits>
#include <entity/base_type/BigInteger.hpp>
#include <gtest/gtest.h>

namespace gtest_case {
  TEST(TestBigInteger, DefaultConstructor) {
    const framework::entity::base_type::BigInteger bi;
    EXPECT_EQ(bi.toString(), "0");
  }

  TEST(TestBigInteger, StringConstructor) {
    EXPECT_EQ(framework::entity::base_type::BigInteger("123").toString(), "123");
    EXPECT_EQ(framework::entity::base_type::BigInteger("-456").toString(), "-456");
    EXPECT_EQ(framework::entity::base_type::BigInteger("0").toString(), "0");
  }

  TEST(TestBigInteger, IntConstructor) {
    EXPECT_EQ(framework::entity::base_type::BigInteger(0).toString(), "0");
    EXPECT_EQ(framework::entity::base_type::BigInteger(123).toString(), "123");
    EXPECT_EQ(framework::entity::base_type::BigInteger(-456).toString(), "-456");
    EXPECT_EQ(framework::entity::base_type::BigInteger(std::numeric_limits<int64_t>::max()).toString(), std::to_string(std::numeric_limits<int64_t>::max()));
    EXPECT_EQ(framework::entity::base_type::BigInteger(std::numeric_limits<int64_t>::min()).toString(), std::to_string(std::numeric_limits<int64_t>::min()));
  }

  TEST(TestBigInteger, Addition) {
    EXPECT_EQ((framework::entity::base_type::BigInteger("100") + framework::entity::base_type::BigInteger("200")).toString(), "300");
    EXPECT_EQ((framework::entity::base_type::BigInteger("-150") + framework::entity::base_type::BigInteger("100")).toString(), "-50");
    EXPECT_EQ((framework::entity::base_type::BigInteger("9999999999999999") + framework::entity::base_type::BigInteger("1")).toString(), "10000000000000000");
  }

  TEST(TestBigInteger, Subtraction) {
    EXPECT_EQ((framework::entity::base_type::BigInteger("200") - framework::entity::base_type::BigInteger("100")).toString(), "100");
    EXPECT_EQ((framework::entity::base_type::BigInteger("100") - framework::entity::base_type::BigInteger("200")).toString(), "-100");
    EXPECT_EQ((framework::entity::base_type::BigInteger("500") - framework::entity::base_type::BigInteger("500")).toString(), "0");
  }

  TEST(TestBigInteger, Multiplication) {
    EXPECT_EQ((framework::entity::base_type::BigInteger("10") * framework::entity::base_type::BigInteger("20")).toString(), "200");
    EXPECT_EQ((framework::entity::base_type::BigInteger("-3") * framework::entity::base_type::BigInteger("7")).toString(), "-21");
    EXPECT_EQ((framework::entity::base_type::BigInteger("0") * framework::entity::base_type::BigInteger("123")).toString(), "0");
    EXPECT_EQ((framework::entity::base_type::BigInteger("123456789") * framework::entity::base_type::BigInteger("987654321")).toString(), "121932631112635269");
  }

  TEST(TestBigInteger, Division) {
    EXPECT_EQ((framework::entity::base_type::BigInteger("20") / framework::entity::base_type::BigInteger("4")).toString(), "5");
    EXPECT_EQ((framework::entity::base_type::BigInteger("-20") / framework::entity::base_type::BigInteger("3")).toString(), "-6");
    EXPECT_THROW(framework::entity::base_type::BigInteger("10") / framework::entity::base_type::BigInteger("0"), std::invalid_argument);
  }

  TEST(TestBigInteger, Modulo) {
    EXPECT_EQ((framework::entity::base_type::BigInteger("10") % framework::entity::base_type::BigInteger("3")).toString(), "1");
    EXPECT_EQ((framework::entity::base_type::BigInteger("-10") % framework::entity::base_type::BigInteger("3")).toString(), "-1");
    EXPECT_THROW(framework::entity::base_type::BigInteger("10") % framework::entity::base_type::BigInteger("0"), std::invalid_argument);
  }

  TEST(TestBigInteger, EqualityOperators) {
    const framework::entity::base_type::BigInteger a("123");
    const framework::entity::base_type::BigInteger b("123");
    const framework::entity::base_type::BigInteger c("456");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_FALSE(a == c);
  }

  TEST(TestBigInteger, ComparisonOperators) {
    const framework::entity::base_type::BigInteger a("100");
    const framework::entity::base_type::BigInteger b("200");
    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= framework::entity::base_type::BigInteger("100"));
    EXPECT_TRUE(b >= a);
    EXPECT_TRUE(a >= framework::entity::base_type::BigInteger("100"));
  }

  TEST(TestBigInteger, ToStringFromString) {
    const framework::entity::base_type::BigInteger original("1234567890");
    const std::string str = original.toString();
    const framework::entity::base_type::BigInteger copied = framework::entity::base_type::BigInteger::fromString(str);
    EXPECT_EQ(copied.toString(), str);
  }

  TEST(TestBigInteger, FromInt) {
    EXPECT_EQ(framework::entity::base_type::BigInteger::fromInt(0).toString(), "0");
    EXPECT_EQ(framework::entity::base_type::BigInteger::fromInt(12345).toString(), "12345");
    EXPECT_EQ(framework::entity::base_type::BigInteger::fromInt(-6789).toString(), "-6789");
    EXPECT_EQ(framework::entity::base_type::BigInteger::fromInt(std::numeric_limits<int64_t>::max()).toString(), std::to_string(std::numeric_limits<int64_t>::max()));
    EXPECT_EQ(framework::entity::base_type::BigInteger::fromInt(std::numeric_limits<int64_t>::min()).toString(), std::to_string(std::numeric_limits<int64_t>::min()));
  }
} // namespace TestBigInteger
