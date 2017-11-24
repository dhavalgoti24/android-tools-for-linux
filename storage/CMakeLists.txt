cmake_minimum_required(VERSION 2.8)
project (android-tools C CXX)
set(SOURCES
 ${PROJECT_SOURCE_DIR}/libnl/lib/cache.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/data.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/nl.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/doc.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/cache_mngr.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/addr.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/fib_lookup/lookup.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/fib_lookup/request.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/msg.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/object.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/socket.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/attr.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/utils.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/cache_mngt.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/handlers.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/genl/ctrl.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/genl/mngt.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/genl/family.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/genl/genl.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/route/rtnl.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/route/route_utils.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/netfilter/nfnl.c
 ${PROJECT_SOURCE_DIR}/libnl/lib/error.c
)

add_definitions (
    -D_GNU_SOURCE
)

#static link
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

add_definitions( -std=c++14 )
include_directories (${PROJECT_SOURCE_DIR}/libnl/include)
add_library(nl ${SOURCES})

file(GLOB IOTOP_SOURCES "${PROJECT_SOURCE_DIR}/iotop/*.cpp")
add_executable(iotop ${IOTOP_SOURCES})
target_link_libraries(iotop nl)

add_executable(taskstats ${PROJECT_SOURCE_DIR}/taskstats/taskstats.c)
target_link_libraries(taskstats nl m)

add_executable(latencytop ${PROJECT_SOURCE_DIR}/latencytop/latencytop.c)
target_link_libraries(latencytop)
