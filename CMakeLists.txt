cmake_minimum_required(VERSION 3.24)

project(HTTP_server LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)
add_executable(http_server
        "${CMAKE_SOURCE_DIR}/apps/main.cpp"
)

add_library(server
        "${CMAKE_SOURCE_DIR}/src/server/http_server.cpp"
        "${CMAKE_SOURCE_DIR}/src/server/http_router.cpp"
)
target_include_directories(server PUBLIC
        "${CMAKE_SOURCE_DIR}/include/"
)

add_library(http
        "${CMAKE_SOURCE_DIR}/src/http/http_query_parser.cpp")
target_include_directories(http PUBLIC
        "${CMAKE_SOURCE_DIR}/include/")

add_library(calculator
        "${CMAKE_SOURCE_DIR}/src/calculator/calculator.cpp"
)
target_include_directories(calculator PUBLIC
        "${CMAKE_SOURCE_DIR}/include/"
)

add_library(utils
        "${CMAKE_SOURCE_DIR}/src/utils/file_utils.cpp"
        "${CMAKE_SOURCE_DIR}/src/utils/time_utils.cpp")
target_include_directories(utils PUBLIC
        "${CMAKE_SOURCE_DIR}/include/")

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/static/index.html"
        "${CMAKE_CURRENT_BINARY_DIR}/static/index.html"
        COPYONLY
)

find_package(Boost CONFIG REQUIRED)
find_package(Threads REQUIRED)
target_link_libraries(http_server PRIVATE
        server
)
target_link_libraries(server PRIVATE
        http
        calculator
        utils
        Boost::headers
        Threads::Threads
)