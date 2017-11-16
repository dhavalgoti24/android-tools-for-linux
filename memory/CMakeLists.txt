cmake_minimum_required(VERSION 2.8)
project (android-tools C CXX)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/libpagemap/*.c")
#file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/libpagemap/*.cpp")
add_definitions (
    -D_LARGEFILE64_SOURCE
    -D_GNU_SOURCE
    )
include_directories (${PROJECT_SOURCE_DIR}/libpagemap/include)
add_library(pagemap ${SOURCES})

add_executable(procmem  ${PROJECT_SOURCE_DIR}/procmem/procmem.c)
target_link_libraries(procmem pagemap)
add_executable(procrank  ${PROJECT_SOURCE_DIR}/procrank/procrank.c)
target_link_libraries(procrank pagemap)

add_executable(showmap  ${PROJECT_SOURCE_DIR}/showmap/showmap.cpp)
target_link_libraries(showmap)
add_executable(showslab  ${PROJECT_SOURCE_DIR}/showslab/showslab.c)
target_link_libraries(showslab)
