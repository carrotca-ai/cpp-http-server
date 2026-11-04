#ifndef HTTP_CALCULATOR_HTTP_REQUEST_HPP
#define HTTP_CALCULATOR_HTTP_REQUEST_HPP
#include <stdexcept>
#include <sstream>
#include <string>

namespace http {
    class Request
    {
        std::string m_method{};
        std::string m_route{};
        std::string m_version{};
    public:
        explicit Request(const std::string& request)
        {
            std::istringstream requestStream{request};

            if (!(requestStream >> m_method >> m_route >> m_version))
            {
                throw std::runtime_error("Invalid HTTP request");
            }
        }
        [[nodiscard]] const std::string& getMethod() const { return m_method; }
        [[nodiscard]] const std::string& getRoute() const { return m_route; }
        [[nodiscard]] std::string_view getPath() const
        {
            std::string_view route{ m_route };
            if (route.find('?') != std::string::npos)
                return route.substr(0, route.find('?'));
            return route;
        }
        [[nodiscard]] std::string_view getQuery() const
        {
            std::string_view route{ m_route };
            if (route.find('?') != std::string::npos)
                return route.substr(route.find('?')+1);
            return "";
        }
        [[nodiscard]] const std::string& getVersion() const { return m_version; }
    };
}
#endif //HTTP_CALCULATOR_HTTP_REQUEST_HPP
