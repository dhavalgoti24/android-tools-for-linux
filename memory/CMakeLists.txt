cmake_minimum_required(VERSION 2.8)
project (android-tools C CXX)
add_definitions (
    -D_LARGEFILE64_SOURCE
    -D_GNU_SOURCE
    -Os
    -std=c++11
)
include_directories (${PROJECT_SOURCE_DIR}/libpagemap/include)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/libpagemap/*.c")
add_library(pagemap STATIC ${SOURCES})

#static link
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

add_executable(procmem  ${PROJECT_SOURCE_DIR}/procmem/procmem.c)
target_link_libraries(procmem pagemap)
add_executable(procrank  ${PROJECT_SOURCE_DIR}/procrank/procrank.c)
target_link_libraries(procrank pagemap)

add_executable(showmap  ${PROJECT_SOURCE_DIR}/showmap/showmap.cpp)
target_link_libraries(showmap)
add_executable(showslab  ${PROJECT_SOURCE_DIR}/showslab/showslab.c)
target_link_libraries(showslab)
add_executable(zram-perf  ${PROJECT_SOURCE_DIR}/zram-perf/zram-perf.cpp)
target_link_libraries(zram-perf)
add_executable(dumpcache  ${PROJECT_SOURCE_DIR}/pagecache/dumpcache.c)
target_link_libraries(dumpcache)
