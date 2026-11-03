#ifndef HTTP_CALCULATOR_HTTP_RESPONSE_HPP
#define HTTP_CALCULATOR_HTTP_RESPONSE_HPP
#include <string>
#include "http_constants.hpp"

namespace http
{
    struct Response
    {
        std::string statusCode{http::S500};
        std::string contentType{http::TEXT_PLAIN};
        std::string body{};

        [[nodiscard]] std::string serialize() const
        {
            return "HTTP/1.1 " + statusCode + "\r\n"
                + "Content-Type: " + contentType + "\r\n"
                + "Content-Length: " + std::to_string(body.size()) + "\r\n"
                + "Connection: close\r\n"
                + "\r\n"
                + body;
        }
    };
}
#endif //HTTP_CALCULATOR_HTTP_RESPONSE_HPP
