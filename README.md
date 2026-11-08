# C++ HTTP Server

## Overview

This project is a simple HTTP/1.1 server written in C++. It uses Boost.Asio for synchronous TCP networking

The server provides calculator API, a current time endpoint, and static HTML serving

## Features

1. HTTP/1.1 request handling
2. Query parameter parsing and validation
3. Calculator API and current time endpoint
4. Static HTML serving
5. Unit testing with GoogleTest

## Build and Run

To build, test, and run the server on a specified port:
```bash
./run.sh 8000
```

To build manually via CMake:
```bash
cmake -S . -B build -D SERVER_PORT=8000
cmake --build build --parallel
```

To test manually via CTest:
```bash
ctest --test-dir build --output-on-failure
```

To run manually:
```bash
./build/http_server
```

## API Endpoints

| Method | Endpoint | Description |
|--------|----------|-------------|
| `GET` | `/` | Serves the calculator HTML page |
| `GET` | `/api/calculate` | Perfroms calculations via query parameters |
| `GET` | `/api/time` | Returns the current server time |   

### Calculator API

| Parameter | Type | Description|
|-----------|------|------------|
| `a` | `double` | First operand |
| `b` | `double` | Second operand |
| `op` | `string` | Arithmetic operator |
Supported operations: `add`, `subtract`, `multiply`, `divide`.

#### Example Request

```bash
curl -i "http://localhost:8000/api/calculate?a=1&b=2&op=add"
```

Expected response:
```http
HTTP/1.1 200 OK
Content-Type: text/plain
Content-Length: 8
Connection: close

3.000000
```

## Requirements

| Dependency | Version | Purpose |
|------------|---------|---------|
| `C++ Compiler` | `C++20 support` | Compiling the server |
| `CMake` | `3.24+` | Build configuration |
| `Boost.Asio` | `1.90.0` | TCP networking |
| `GoogleTest` | `1.18.0` | Unit testing |
| `Git` | `Any recent` | Fetching GoogleTest via CMake |

## Limitations

1. Synchronous I/O (connections are handled sequentially)
2. No connection timeouts
3. Limited HTTP/1.1 support