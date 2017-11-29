cmake_minimum_required(VERSION 2.8)
project (android-tools C CXX)
add_definitions (
    -D_GNU_SOURCE
)

add_executable(crypto-perf  ${PROJECT_SOURCE_DIR}/crypto-perf/crypto.cpp)
target_link_libraries(crypto-perf)
