#!/usr/bin/env bash
set -e
cd "$(dirname "$(realpath "$0")")"

PORT="${1:-8000}"

cmake -S . -B build -D SERVER_PORT="$PORT"
cmake --build build --parallel

ctest --test-dir build --output-on-failure

echo "Starting server on port $PORT..."
./build/http_server