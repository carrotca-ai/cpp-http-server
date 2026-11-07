#ifndef HTTP_CALCULATOR_ROUTER_HPP
#define HTTP_CALCULATOR_ROUTER_HPP

#include "http/http_request.hpp"
#include "http/http_response.hpp"
namespace server
{
    http::Response route(const http::Request& request);
}
#endif //HTTP_CALCULATOR_ROUTER_HPP
