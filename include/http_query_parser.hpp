#ifndef HTTP_CALCULATOR_HTTP_QUERY_PARSER_HPP
#define HTTP_CALCULATOR_HTTP_QUERY_PARSER_HPP
#include <vector>
#include "http_request.hpp"
namespace http
{
    // throws std::invalid_argument if a query parameter is malformed
    std::vector<std::pair<std::string, std::string>> parseQuery(const http::Request& request);
}
#endif //HTTP_CALCULATOR_HTTP_QUERY_PARSER_HPP
