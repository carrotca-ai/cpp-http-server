#ifndef HTTP_CALCULATOR_HTTP_RESPONSE_HPP
#define HTTP_CALCULATOR_HTTP_RESPONSE_HPP
#include <string>

namespace http
{
    struct Response
    {
        std::string statusCode{};
        std::string contentType{};
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
