#ifndef HTTP_SERVER_V2_CALCULATOR_HPP
#define HTTP_SERVER_V2_CALCULATOR_HPP
#include <string_view>
namespace calc
{
    // throws std::invalid_argument on division by 0 OR an unknown operation
     double calculate(double num1,
        std::string_view operation,
        double num2);
}
#endif
