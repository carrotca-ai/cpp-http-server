cmake_minimum_required(VERSION 3.24)

project(HTTP_server LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.18.0
)
FetchContent_MakeAvailable(googletest)

if(NOT DEFINED SERVER_PORT)
    set(SERVER_PORT 8000)
endif()

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

target_compile_definitions(server PUBLIC SERVER_PORT=${SERVER_PORT})

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

enable_testing()

add_executable(calculator_tests
        "${CMAKE_SOURCE_DIR}/tests/calculator_test.cpp"
)
target_link_libraries(calculator_tests PRIVATE
        calculator
        GTest::gtest_main
)

add_executable(query_parser_tests
        "${CMAKE_SOURCE_DIR}/tests/query_parser_test.cpp"
)
target_link_libraries(query_parser_tests PRIVATE
        http
        GTest::gtest_main
)

add_executable(http_request_tests
        "${CMAKE_SOURCE_DIR}/tests/http_request_test.cpp"
)
target_link_libraries(http_request_tests PRIVATE
        http
        GTest::gtest_main
)

add_executable(http_response_tests
        "${CMAKE_SOURCE_DIR}/tests/http_response_test.cpp"
)
target_link_libraries(http_response_tests PRIVATE
        http
        GTest::gtest_main
)

add_executable(http_router_tests
        "${CMAKE_SOURCE_DIR}/tests/http_router_test.cpp"
)
target_link_libraries(http_router_tests PRIVATE
        server
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(calculator_tests)
gtest_discover_tests(http_request_tests)
gtest_discover_tests(http_response_tests)
gtest_discover_tests(query_parser_tests)
gtest_discover_tests(http_router_tests)
