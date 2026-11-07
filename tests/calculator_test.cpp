#include <gtest/gtest.h>
#include "calculator/calculator.hpp"
#include <stdexcept>

TEST(CalculatorTest, Addition)
{
    const double result{calc::calculate(3.0, "add", 2.0)};
    EXPECT_DOUBLE_EQ(result, 5.0);
}
TEST(CalculatorTest, Subtraction)
{
    const double result{calc::calculate(3.0, "subtract", 2.0)};
    EXPECT_DOUBLE_EQ(result, 1.0);
}
TEST(CalculatorTest, Multiplication)
{
    const double result{calc::calculate(3.0, "multiply", 2.0)};
    EXPECT_DOUBLE_EQ(result, 6.0);
}
TEST(CalculatorTest, Division)
{
    const double result{calc::calculate(3.0, "divide", 2.0)};
    EXPECT_DOUBLE_EQ(result, 1.5);
}
TEST(CalculatorTest, DivisionByZero)
{
    EXPECT_THROW
    (
        calc::calculate(3.0, "divide", 0.0),
        std::invalid_argument
    );
}
TEST(CalculatorTest, UnknownOperation)
{
    EXPECT_THROW
    (
        calc::calculate(3.0, "unknown", 0.0),
        std::invalid_argument
    );
}