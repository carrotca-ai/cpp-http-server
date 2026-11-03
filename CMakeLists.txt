cmake_minimum_required(VERSION 3.24)

project(HTTP_calculator LANGUAGES CXX)

add_executable(http_calculator
        "${CMAKE_SOURCE_DIR}/apps/main.cpp"
        "${CMAKE_SOURCE_DIR}/src/calculator.cpp"
        "${CMAKE_SOURCE_DIR}/src/http_server.cpp"
        "${CMAKE_SOURCE_DIR}/src/time_utils.cpp"
        "${CMAKE_SOURCE_DIR}/src/http_router.cpp"
        "${CMAKE_SOURCE_DIR}/src/file_utils.cpp"
        "${CMAKE_SOURCE_DIR}/src/http_query_parser.cpp")
target_compile_features(http_calculator PRIVATE cxx_std_20)
target_compile_options(http_calculator PRIVATE
        -Wall
        -Wextra
        -Wpedantic)
target_include_directories(http_calculator PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/static/index.html"
        "${CMAKE_CURRENT_BINARY_DIR}/static/index.html"
        COPYONLY
)

find_package(Boost CONFIG REQUIRED)
find_package(Threads REQUIRED)
target_link_libraries(http_calculator PRIVATE
        Boost::headers
        Threads::Threads)
