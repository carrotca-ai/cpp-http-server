#include <gtest/gtest.h>
#include "http/http_request.hpp"
#include "http/http_query_parser.hpp"
#include <string>
#include <stdexcept>

TEST(QueryParserTest, NormalValue)
{
    const http::QueryParams result {http::parseQuery(http::Request{"GET /api/test?a=1 HTTP/1.1"})};
    const http::QueryParams expectedResult {{"a", "1"}};
    EXPECT_EQ(result, expectedResult);
}

TEST(QueryParserTest, DecimalValue)
{
    const http::QueryParams result {http::parseQuery(http::Request{"GET /api/test?a=1.1 HTTP/1.1"})};
    const http::QueryParams expectedResult {{"a", "1.1"}};
    EXPECT_EQ(result, expectedResult);
}

TEST(QueryParserTest, NegativeValue)
{
    const http::QueryParams result {http::parseQuery(http::Request{"GET /api/test?a=-1 HTTP/1.1"})};
    const http::QueryParams expectedResult {{"a", "-1"}};
    EXPECT_EQ(result, expectedResult);
}

TEST(QueryParserTest, EmptyValue)
{
    const http::QueryParams result {http::parseQuery(http::Request{"GET /api/test?a= HTTP/1.1"})};
    const http::QueryParams expectedResult {{"a", ""}};
    EXPECT_EQ(result, expectedResult);
}

TEST(QueryParserTest, EmptyQuery)
{
    const http::QueryParams result {http::parseQuery(http::Request{"GET /api/test HTTP/1.1"})};
    const http::QueryParams expectedResult {};
    EXPECT_EQ(result, expectedResult);
}

TEST(QueryParserTest, ComplexParameters)
{
    const http::QueryParams result{http::parseQuery(http::Request{"GET /api/test?a=1&b=4&c=5.2&d=&e=0 HTTP/1.1"})};
    const http::QueryParams expectedResult {{"a", "1"}, {"b", "4"}, {"c", "5.2"}, {"d", ""}, {"e", "0"}};
    EXPECT_EQ(result, expectedResult);
}

TEST(QueryParserTest, EmptyKeyWithAmpersand)
{
    EXPECT_THROW
    (
        http::parseQuery(http::Request{"GET /api/test?a=7&=b HTTP/1.1"}),
        std::invalid_argument
    );
}

TEST(QueryParserTest, EmptyKeyWithoutAmpersand)
{
    EXPECT_THROW
    (
        http::parseQuery(http::Request{"GET /api/test?=7 HTTP/1.1"}),
        std::invalid_argument
    );
}

TEST(QueryParserTest, DoubleAmpersand)
{
    EXPECT_THROW
    (
        http::parseQuery(http::Request{"GET /api/test?a=1&&b=2 HTTP/1.1"}),
        std::invalid_argument
    );
}

TEST(QueryParserTest, MissingEquality)
{
    EXPECT_THROW
    (
        http::parseQuery(http::Request{"GET /api/test?a=1&b HTTP/1.1"}),
        std::invalid_argument
    );
}

TEST(QueryParserTest, MissingEqualityWithoutAmpersand)
{
    EXPECT_THROW
    (
        http::parseQuery(http::Request{"GET /api/test?a HTTP/1.1"}),
        std::invalid_argument
    );
}

TEST(QueryParserTest, AmpersandAtEnd)
{
    EXPECT_THROW
    (
        http::parseQuery(http::Request{"GET /api/test?a=1& HTTP/1.1"}),
        std::invalid_argument
    );
}
TEST(QueryParserTest, AmpersandAtStart)
{
    EXPECT_THROW
    (
        http::parseQuery(http::Request{"GET /api/test?&a=1 HTTP/1.1"}),
        std::invalid_argument
    );
}

TEST(QueryParserTest, ExtraEquality)
{
    EXPECT_THROW
    (
        http::parseQuery(http::Request{"GET /api/test?a=1=2 HTTP/1.1"}),
        std::invalid_argument
    );
}
