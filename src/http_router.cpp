#include "http_router.hpp"
#include "calculator.hpp"
#include "file_utils.hpp"
#include "http_keywords.hpp"
#include "time_utils.hpp"
#include "http_server_config.hpp"
#include "http_query_parser.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>

namespace server
{
    http::Response route(http::Request& request)
    {
        http::Response response{};
        const std::string& route{request.getRoute()};
        if (request.getMethod() != http::GET)
        {
            response.statusCode = http::S405;
            response.contentType = http::TEXT_PLAIN;
            response.body = "Method not allowed";
        }
        else if (route == "/")
        {
            response.statusCode = http::S200;
            response.contentType = http::TEXT_HTML;
            response.body = file_utils::readFileStr(server_config::static_files::indexHtmlPath);
        }
        else if (route.starts_with("/api/calculate?"))
        {
            std::vector<std::pair<std::string, std::string>> test{http::parseQuery(request)};
            for (const auto& pair : test) {
                std::cout << pair.first << ": " << pair.second << std::endl;
            }
            response.contentType = http::TEXT_PLAIN;
            response.statusCode = http::S200;
            try
            {
            const auto aStart = route.find("a=") + 2;
            const auto aEnd = route.find("&b=");
            const auto bStart = route.find("b=") + 2;
            const auto bEnd = route.find("&op=");

            const double num1{
                std::stod(route.substr(aStart, aEnd - aStart))
            };
            const double num2{
                std::stod(route.substr(bStart, bEnd - bStart))
            };
            const std::string operation{
                route.substr(route.find("op=") + 3)
            };
                double result{calc::calculate(num1, operation, num2)};
                response.body = std::to_string(result);
            }
            catch (const std::invalid_argument& e)
            {
                response.statusCode = http::S400;
                response.body = e.what();

            }
            catch (const std::out_of_range&)
            {
                response.statusCode = http::S400;
                response.body = "Number out of range";
            }
        }
        else if (route == "/api/time" || route == "/api/time/")
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
