#include <gtest/gtest.h>
#include "http/http_response.hpp"
#include <string>
#include "http/http_constants.hpp"

TEST(HttpResponseTest, NormalResponse)
{
    const http::Response result{std::string{http::S200}, std::string{http::TEXT_PLAIN}, "Hello"};
    const std::string expectedResult{
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 5\r\n"
        "Connection: close\r\n"
        "\r\n"
        "Hello"
    };
    EXPECT_EQ(result.serialize(), expectedResult);
}

TEST(HttpResponseTest, EmptyBody)
{
    const http::Response result{std::string{http::S200}, std::string{http::TEXT_PLAIN}, ""};
    const std::string expectedResult{
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 0\r\n"
        "Connection: close\r\n"
        "\r\n"};
    EXPECT_EQ(result.serialize(), expectedResult);
}

TEST(HttpResponseTest, ErrorResponse)
{
    const http::Response result{std::string{http::S404}, std::string{http::TEXT_PLAIN}, "Page not found"};
    const std::string expectedResult{
        "HTTP/1.1 404 Not Found\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 14\r\n"
        "Connection: close\r\n"
        "\r\n"
        "Page not found"
    };
    EXPECT_EQ(result.serialize(), expectedResult);
}

TEST(HttpResponseTest, DefaultResponse)
{
    const http::Response result{};
    const std::string expectedResult{
        "HTTP/1.1 500 Internal Server Error\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 0\r\n"
        "Connection: close\r\n"
        "\r\n"
    };
    EXPECT_EQ(result.serialize(), expectedResult);
}