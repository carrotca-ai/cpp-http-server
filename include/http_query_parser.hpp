#ifndef HTTP_CALCULATOR_HTTP_QUERY_PARSER_HPP
#define HTTP_CALCULATOR_HTTP_QUERY_PARSER_HPP
#include <vector>
#include "http_request.hpp"
namespace http
{
    using QueryParams = std::vector<std::pair<std::string, std::string>>;
    // throws std::invalid_argument if a query parameter is malformed
    QueryParams parseQuery(const http::Request& request);
}
#endif //HTTP_CALCULATOR_HTTP_QUERY_PARSER_HPP
