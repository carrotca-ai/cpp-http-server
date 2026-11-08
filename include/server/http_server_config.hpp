#ifndef HTTP_CALCULATOR_HTTP_SERVER_CONFIG_HPP
#define HTTP_CALCULATOR_HTTP_SERVER_CONFIG_HPP
#include <string_view>
namespace server_config
{
    constexpr unsigned short port{SERVER_PORT};
}
namespace server_config::static_files
{
    constexpr std::string_view indexHtmlPath{"static/index.html"};
}

#endif //HTTP_CALCULATOR_HTTP_SERVER_CONFIG_HPP
