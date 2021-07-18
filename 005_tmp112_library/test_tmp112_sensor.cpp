#include <gtest/gtest.h>
extern "C" {
#include "tmp112_sensor.h"
}

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);

  EXPECT_EQ(2, init());
}
