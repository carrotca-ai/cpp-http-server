#include "calculator/calculator.hpp"

#include <stdexcept>

namespace calc
{
    double calculate(const double num1, const std::string_view operation, const double num2)
    {
        if (operation == "add")
        {
            return num1 + num2;
        }
        else if (operation == "subtract")
        {
            return num1 - num2;
        }
        else if (operation == "multiply")
        {
            return num1 * num2;
        }
        else if (operation == "divide")
        {
            if (num2 == 0)
            {
                throw std::invalid_argument{"Division by zero"};
            }
            return num1 / num2;
        }
        else
        {
            throw std::invalid_argument("Unknown operation");
        }
    }
}
