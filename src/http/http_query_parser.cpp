#include "http/http_query_parser.hpp"

#include <stdexcept>
#include "http/http_request.hpp"
namespace http
{
    //forward declaration of query validation
    namespace {
        void validateQuery(const std::vector<size_t>& equalPos, const std::vector<size_t>& ampPos   );
    }
    QueryParams parseQuery(const http::Request& request)
    {
        std::string query{ request.getQuery()};
        if (query.empty())
        {
            return {};
        }
        std::vector<size_t> ampPos{};
        std::vector<size_t> equalPos{};
        QueryParams params{};
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
        validateQuery(equalPos, ampPos);
        if (ampPos.empty())
            params.push_back({{query.substr(0, equalPos[0])}, {query.substr(equalPos[0] + 1)}});
        else
            params.push_back({{query.substr(0, equalPos[0])}, {query.substr(equalPos[0] + 1, ampPos[0] - equalPos[0] - 1)}});
        for (size_t i{1}; i < equalPos.size(); ++i)
        {
            if (equalPos[i] == equalPos.back())
                params.push_back({{query.substr(ampPos[i - 1] + 1, equalPos[i] - ampPos[i - 1] - 1)}, {query.substr(equalPos[i] + 1)}});
            else
                params.push_back({{query.substr(ampPos[i - 1] + 1, equalPos[i] - ampPos[i - 1] - 1)}, {query.substr(equalPos[i] + 1, ampPos[i] - equalPos[i] - 1)}});
        }
        return params;
    }
    namespace
    {
        void validateQuery(const std::vector<size_t>& equalPos, const std::vector<size_t>& ampPos)
        {
            if (equalPos.empty())
                throw std::invalid_argument("Missing '=' in query");
            if (equalPos[0] == 0)
                throw std::invalid_argument("Query parameter key must not be empty");
            if (ampPos.size() != equalPos.size() - 1)
                throw std::invalid_argument("Invalid number of query delimiters");
            for (size_t i{0}; i < ampPos.size(); ++i)
            {
                if (ampPos[i] > equalPos[i + 1] || ampPos[i] < equalPos[i])
                    throw std::invalid_argument("Query is malformed");
                if (equalPos[i + 1] == ampPos[i] + 1)
                {
                    throw std::invalid_argument("Query parameter key must not be empty");
                }
            }
        }
    }
}
