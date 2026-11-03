#include "http_router.hpp"
#include <cmath>
#include "calculator.hpp"
#include "file_utils.hpp"
#include "http_constants.hpp"
#include "time_utils.hpp"
#include "http_server_config.hpp"
#include "http_query_parser.hpp"
#include <string>
#include <string_view>
#include <iostream>
#include <stdexcept>
namespace server {
    http::Response route(http::Request& request)
    {
        http::Response response{};
        const std::string_view path{request.getPath()};
        if (request.getMethod() != http::GET)
        {
            response.statusCode = http::S405;
            response.contentType = http::TEXT_PLAIN;
            response.body = "Method not allowed";
        }
        else if (path == "/")
        {
            response.statusCode = http::S200;
            response.contentType = http::TEXT_HTML;
            try
            {
                response.body = file_utils::readFileStr(server_config::static_files::indexHtmlPath);
            }
            catch (const std::exception& e)
            {
                response.statusCode = http::S500;
                response.contentType = http::TEXT_PLAIN;
                response.body = "Internal Server Error";
                std::cerr << e.what() << std::endl;
            }
        }
        else if (path == "/api/calculate")
        {
            response.statusCode = http::S200;
            response.contentType = http::TEXT_PLAIN;
            try
            {

                http::QueryParams params{http::parseQuery(request)};
#ifndef NDEBUG
                for (const auto& param : params) {
                    std::cout << param.first << ": " << param.second << std::endl;
                }
#endif
                double num1{};
                bool hasA{};
                double num2{};
                bool hasB{};
                std::string op{};
                bool hasOp{};
                size_t processed{};
                if (params.size() != 3)
                    throw std::invalid_argument("Expected 3 query parameters");
                 for (const auto& param : params)
                 {
                     if (param.first == "a" && !hasA)
                     {
                         hasA = true;
                         num1 = std::stod(param.second, &processed);
                         if (processed != param.second.size() || !std::isfinite(num1))
                             throw std::invalid_argument("Invalid query parameter");
                     }
                     else if (param.first == "b" && !hasB)
                     {
                         hasB = true;
                         num2 = std::stod(param.second, &processed);
                         if (processed != param.second.size()|| !std::isfinite(num2))
                             throw std::invalid_argument("Invalid query parameter");
                     }
                     else if (param.first == "op" && !hasOp)
                     {
                         hasOp = true;
                         op = param.second;
                     }
                     else
                         throw std::invalid_argument("Invalid query parameter");
                 }
                double result{calc::calculate(num1, op, num2)};
                response.body = std::to_string(result);
            }
            catch (const std::invalid_argument& e)
            {
                response.statusCode = http::S400;
                response.body = e.what();
                std::cerr << e.what() << std::endl;
            }
            catch (const std::out_of_range& e)
            {
                response.statusCode = http::S400;
                response.body = "Number out of range";
                std::cerr << e.what() << std::endl;
            }
        }
        else if (path == "/api/time" || path == "/api/time/")
        {
            response.statusCode = http::S200;
            response.contentType = http::TEXT_PLAIN;
            response.body = time_utils::getCurrentTimeStr();
        }
        else
        {
            response.statusCode = http::S404;
            response.contentType = http::TEXT_PLAIN;
            response.body = "Page not found";
        }
        return response;
    }
}
