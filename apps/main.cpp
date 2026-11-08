#include "server/http_server.hpp"
#include "server/http_server_config.hpp"

int main()
{
    server::run(server_config::port);
}