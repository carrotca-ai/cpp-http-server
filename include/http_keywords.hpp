#ifndef HTTP_CALCULATOR_HTTP_KEYWORDS_HPP
#define HTTP_CALCULATOR_HTTP_KEYWORDS_HPP
#include <string_view>
namespace http
{
    constexpr std::string_view GET{"GET"};
    constexpr std::string_view POST{"POST"};
    constexpr std::string_view CONTENT{"Content-Type"};
    constexpr std::string_view TEXT_PLAIN{"text/plain"};
    constexpr std::string_view TEXT_HTML{"text/html"};
    constexpr std::string_view HTTP{"HTTP"};
    constexpr std::string_view S405{"405 Method not allowed"};
    constexpr std::string_view S404{"404 Not Found"};
    constexpr std::string_view S400{"Bad Request"};
    constexpr std::string_view S200{"200 OK"};
}
#endif //HTTP_CALCULATOR_HTTP_KEYWORDS_HPP
