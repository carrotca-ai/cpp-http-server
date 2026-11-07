#include <gtest/gtest.h>
#include "http/http_request.hpp"
#include "http/http_response.hpp"
#include "server/http_router.hpp"
#include <string>
#include "http/http_constants.hpp"
#include <stdexcept>
TEST(HttpRouterTest, NormalRoute)
{
    const http::Response result (server::route(http::Request{"GET / HTTP/1.1"}));
    EXPECT_EQ(result.statusCode, http::S200);
    EXPECT_EQ(result.contentType, http::TEXT_HTML);
}

TEST(HttpRouterTest, NotFoundRoute)
{
    const http::Response result (server::route(http::Request{"GET /not-found HTTP/1.1"}));
    EXPECT_EQ(result.statusCode, http::S404);
    EXPECT_EQ(result.contentType, http::TEXT_PLAIN);
}

TEST(HttpRouterTest, MethodNotAllowed)
{
    const http::Response result (server::route(http::Request{"PUT / HTTP/1.1"}));
    EXPECT_EQ(result.statusCode, http::S405);
    EXPECT_EQ(result.contentType, http::TEXT_PLAIN);
    EXPECT_EQ(result.body, "Method not allowed");
}

TEST(HttpRouterTest, CalculatorRoute)
{
    const http::Response result (server::route(http::Request{"GET /api/calculate?a=1&b=2&op=add HTTP/1.1"}));
    EXPECT_EQ(result.statusCode, http::S200);
    EXPECT_EQ(result.contentType, http::TEXT_PLAIN);
    EXPECT_EQ(result.body, "3.000000");
}

TEST(HttpRouterTest, CalculatorRouteInvalidOperation)
{
    const http::Response result (server::route(http::Request{"GET /api/calculate?a=1&b=2&op=invalid HTTP/1.1"}));
    EXPECT_EQ(result.statusCode, http::S400);
    EXPECT_EQ(result.contentType, http::TEXT_PLAIN);
    EXPECT_EQ(result.body, "Unknown operation");
}

TEST(HttpRouterTest, CalculatorRouteInvalidQuery)
{
    const http::Response result (server::route(http::Request{"GET /api/calculate?a=1&b=2 HTTP/1.1"}));
    EXPECT_EQ(result.statusCode, http::S400);
    EXPECT_EQ(result.contentType, http::TEXT_PLAIN);
    EXPECT_EQ(result.body, "Expected 3 query parameters");
}

TEST(HttpRouterTest, CalculatorRouteTwoOperations)
{
    const http::Response result (server::route(http::Request{"GET /api/calculate?a=1&op=subtract&op=add HTTP/1.1"}));
    EXPECT_EQ(result.statusCode, http::S400);
    EXPECT_EQ(result.contentType, http::TEXT_PLAIN);
    EXPECT_EQ(result.body, "Invalid query parameter");
}

TEST(HttpRouterTest, CalculatorRouteInvalidKey)
{
    const http::Response result (server::route(http::Request{"GET /api/calculate?e=1&b=2&op=add HTTP/1.1"}));
    EXPECT_EQ(result.statusCode, http::S400);
    EXPECT_EQ(result.contentType, http::TEXT_PLAIN);
    EXPECT_EQ(result.body, "Invalid query parameter");
}

TEST(HttpRouterTest, CalculatorRouteInvalidNumber)
{
    const http::Response result (server::route(http::Request{"GET /api/calculate?a=invalid&b=2&op=add HTTP/1.1"}));
    EXPECT_EQ(result.statusCode, http::S400);
    EXPECT_EQ(result.contentType, http::TEXT_PLAIN);
}

TEST(HttpRouterTest, CalculatorRouteDivisionByZero)
{
    const http::Response result (server::route(http::Request{"GET /api/calculate?a=1&b=0&op=divide HTTP/1.1"}));
    EXPECT_EQ(result.statusCode, http::S400);
    EXPECT_EQ(result.contentType, http::TEXT_PLAIN);
    EXPECT_EQ(result.body, "Division by zero");
}

TEST(HttpRouterTest, CalculatorRouteOutOfRange)
{
    const http::Response result (server::route(http::Request{"GET /api/calculate?a=1e9999&b=0&op=add HTTP/1.1"}));
    EXPECT_EQ(result.statusCode, http::S400);
    EXPECT_EQ(result.contentType, http::TEXT_PLAIN);
    EXPECT_EQ(result.body, "Number out of range");
}

TEST(HttpRouterTest, TimeRoute)
{
    const http::Response result (server::route(http::Request{"GET /api/time HTTP/1.1"}));
    EXPECT_EQ(result.statusCode, http::S200);
    EXPECT_EQ(result.contentType, http::TEXT_PLAIN);
    EXPECT_FALSE(result.body.empty());
}

