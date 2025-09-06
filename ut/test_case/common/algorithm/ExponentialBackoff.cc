#include "algorithm/ExponentialBackoff.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace gtest_case {
TEST(ExponentialBackoffTest, Constructor_InvalidArguments) {
  EXPECT_THROW(fox::ExponentialBackoff(3, 0.0, 2.0), std::invalid_argument);
  EXPECT_THROW(fox::ExponentialBackoff(3, -1.0, 2.0), std::invalid_argument);

  EXPECT_THROW(fox::ExponentialBackoff(3, 100.0, 1.0), std::invalid_argument);
  EXPECT_THROW(fox::ExponentialBackoff(3, 100.0, 0.5), std::invalid_argument);

  EXPECT_THROW(fox::ExponentialBackoff(3, 100.0, 2.0, -1.0), std::invalid_argument);

  EXPECT_THROW(fox::ExponentialBackoff(3, 100.0, 2.0, 0.0, -1.0), std::invalid_argument);

  EXPECT_THROW(fox::ExponentialBackoff(3, 100.0, 2.0, 200.0, 100.0), std::invalid_argument);

  EXPECT_THROW(fox::ExponentialBackoff(3, 50.0, 2.0, 100.0), std::invalid_argument);
}

TEST(ExponentialBackoffTest, GetNextDelay_BasicBehavior) {
  fox::ExponentialBackoff backoff(3, 100.0, 2.0, 50.0, 500.0, 12345u);

  double delay = backoff.getNextDelay();
  EXPECT_GE(delay, 50.0);
  EXPECT_LE(delay, 100.0);

  delay = backoff.getNextDelay();
  EXPECT_GE(delay, 50.0);
  EXPECT_LE(delay, 200.0);

  delay = backoff.getNextDelay();
  EXPECT_GE(delay, 50.0);
  EXPECT_LE(delay, 400.0);

  EXPECT_THROW(backoff.getNextDelay(), std::runtime_error);
}

TEST(ExponentialBackoffTest, Reset_Method) {
  fox::ExponentialBackoff backoff(3, 100.0, 2.0);

  backoff.getNextDelay();
  backoff.getNextDelay();

  backoff.reset();
  const double delay = backoff.getNextDelay();
  EXPECT_LE(delay, 100.0);
}

TEST(ExponentialBackoffTest, IsExhausted_Method) {
  fox::ExponentialBackoff backoff(2, 100.0, 2.0);

  EXPECT_FALSE(backoff.isExhausted());
  backoff.getNextDelay();
  backoff.getNextDelay();
  EXPECT_TRUE(backoff.isExhausted());
}

TEST(ExponentialBackoffTest, ThreadSafe_Mode) {
  fox::ExponentialBackoff backoff(3, 100.0, 2.0, 0.0, 1000.0, 12345u, true);

  std::atomic call_count{0};
  constexpr int num_threads = 10;
  std::vector<std::thread> threads;

  for (int i = 0; i < num_threads; ++i) {
    threads.emplace_back([&] {
      for (int j = 0; j < 5; ++j) {
        if (backoff.isExhausted()) continue;
        backoff.getNextDelay();
        // 可选：验证 delay 在预期范围内
        call_count.fetch_add(1);
      }
    });
  }

  for (auto& t : threads) t.join();

  EXPECT_TRUE(call_count.load() <= backoff.getMaxRetries());
}

TEST(ExponentialBackoffTest, RandomSeed_Fixed) {
  fox::ExponentialBackoff backoff1(3, 100.0, 2.0, 0.0, 1000.0, 12345u);
  fox::ExponentialBackoff backoff2(3, 100.0, 2.0, 0.0, 1000.0, 12345u);

  EXPECT_DOUBLE_EQ(backoff1.getNextDelay(), backoff2.getNextDelay());
  EXPECT_DOUBLE_EQ(backoff1.getNextDelay(), backoff2.getNextDelay());
  EXPECT_DOUBLE_EQ(backoff1.getNextDelay(), backoff2.getNextDelay());
}
}  // namespace gtest_case
