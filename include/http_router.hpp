#ifndef HTTP_CALCULATOR_ROUTER_HPP
#define HTTP_CALCULATOR_ROUTER_HPP

#include "http_request.hpp"
#include "http_response.hpp"
namespace server
{
    http::Response route(http::Request& request);
}
#endif //HTTP_CALCULATOR_ROUTER_HPP
