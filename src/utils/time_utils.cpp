#include "utils/time_utils.hpp"
#include <ctime>
namespace time_utils
{
    std::string getCurrentTimeStr()
    {
        const std::time_t now = std::time(nullptr);
        return std::ctime(&now);
    }
}