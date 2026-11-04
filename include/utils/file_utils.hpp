#ifndef HTTP_CALCULATOR_FILE_UTILS_HPP
#define HTTP_CALCULATOR_FILE_UTILS_HPP
#include <string>
#include <string_view>
namespace file_utils
{
    // throws std::runtime_error if the file cannot be opened
    std::string readFileStr(std::string_view path);
}
#endif //HTTP_CALCULATOR_FILE_UTILS_HPP
