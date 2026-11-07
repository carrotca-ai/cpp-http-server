#include "server/http_server.hpp"

#include <iostream>
#include "http/http_request.hpp"
#include "http/http_response.hpp"
#include "server/http_router.hpp"
#include "boost/asio.hpp"

namespace server
{
    using boost::asio::ip::tcp;
    void run(const unsigned short port)
    {
        try {
            boost::asio::io_context io_context;
            tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port));
            for (;;)
            {
                tcp::socket socket(io_context);
                acceptor.accept(socket);
                boost::system::error_code ec;
                std::string rawRequest;

                boost::asio::read_until(
                    socket,
                    boost::asio::dynamic_buffer(rawRequest),
                    "\r\n\r\n"
                );

                http::Request request{rawRequest};
                std::cout << request.getMethod() << request.getRoute() << request.getVersion() << '\n';
                http::Response response{server::route(request)};

                boost::asio::write(
                         socket,
                         boost::asio::buffer(response.serialize()),
                         ec
                     );
                if (ec)
                {
                    std::cerr << ec.message() << std::endl;
                }
            }
        }
        catch (const boost::system::system_error& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}
