#include <limits.h>
#include "gtest/gtest.h"
#include "calculator.h"


TEST(CalculatorTest, Addition) {
  EXPECT_EQ(2, calculator::plus(1,1)) << "adding 1 to 1 should be 2";
}

TEST(CalculatorTest, Add_zero) {
  EXPECT_EQ(1, calculator::plus(0,1));
  EXPECT_EQ(1, calculator::plus(1,0));
}

TEST(CalculatorTest, Minus) {
  calculator calc;
  EXPECT_EQ(0, calc.minus(1,1));
  EXPECT_EQ(1, calc.minus(2,1));
}

TEST(CalculatorTest, MemoryLeak) {
  calculator* cal = new calculator;
  ASSERT_TRUE(cal);
//  delete cal;
}

TEST(CalculatorTest, CrashTest) {
  calculator* cal = NULL;
  EXPECT_DEATH_IF_SUPPORTED(cal->add(), "");
}

