#include <gtest/gtest.h>
#include "http/http_request.hpp"
#include <string>
#include <stdexcept>

TEST(HttpRequestTest, NormalRequest) {
    const http::Request result{"GET /api/test HTTP/1.1"};
    EXPECT_EQ(result.getMethod(), "GET");
    EXPECT_EQ(result.getRoute(), "/api/test");
    EXPECT_EQ(result.getVersion(),"HTTP/1.1");
}

TEST(HttpRequestTest, MissingVersion)
{
    EXPECT_THROW(
    const http::Request result{"GET /api/test"},
    std::runtime_error
    );
}

TEST(HttpRequestTest, RequestWithQuery)
{
    const http::Request result{"GET /api/test?a=1&d=5 HTTP/1.1"};
    EXPECT_EQ(result.getMethod(), "GET");
    EXPECT_EQ(result.getRoute(), "/api/test?a=1&d=5");
    EXPECT_EQ(result.getQuery(), "a=1&d=5");
    EXPECT_EQ(result.getPath(), "/api/test");
    EXPECT_EQ(result.getVersion(), "HTTP/1.1");
}