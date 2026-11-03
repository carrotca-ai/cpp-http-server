#include "http_query_parser.hpp"

#include <algorithm>
#include <stdexcept>
#include "http_request.hpp"
namespace http
{
    std::vector<std::pair<std::string, std::string>> parseQuery(const http::Request& request)
    {
        std::string query{ request.getQuery()};
        if (query.empty())
        {
            return {};
        }
        std::vector<size_t> ampPos{};
        std::vector<size_t> equalPos{};
        std::vector<std::pair<std::string, std::string>> params{};
        for (size_t i{0}; i < query.length(); ++i)
        {
            if (query[i] == '&')
            {
                ampPos.push_back(i);
            }
            if (query[i] == '=')
            {
                equalPos.push_back(i);
            }
        }
        if (equalPos.empty())
            throw std::invalid_argument("Missing '=' in query");
        if (ampPos.empty())
            params.push_back({{query.substr(0, equalPos[0])}, {query.substr(equalPos[0] + 1)}});
        else
            params.push_back({{query.substr(0, equalPos[0])}, {query.substr(equalPos[0] + 1, ampPos[0] - equalPos[0] - 1)}});
        for (size_t i{1}; i < equalPos.size(); ++i)
        {
            if (equalPos[i] == equalPos[equalPos.size() - 1])
                params.push_back({{query.substr(ampPos[i - 1] + 1, equalPos[i] - ampPos[i - 1] - 1)}, {query.substr(equalPos[i] + 1)}});

            else
                params.push_back({{query.substr(ampPos[i - 1] + 1, equalPos[i] - ampPos[i - 1] - 1)}, {query.substr(equalPos[i] + 1, ampPos[i] - equalPos[i] - 1)}});
        }
        return params;
    }
}
