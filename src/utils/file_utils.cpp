#include "utils/file_utils.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
namespace file_utils
{
    std::string readFileStr(std::string_view path)
    {
        std::ifstream file(std::string{path}, std::ios::binary);
        if (!file)
        {
            throw std::runtime_error{std::string{path} + " cannot be opened"};
        }
        std::ostringstream oss{};
        oss << file.rdbuf();
        return oss.str();
    }
}
