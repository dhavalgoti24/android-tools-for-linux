cmake_minimum_required(VERSION 2.8)
add_definitions (
 -Os -g -W -Wall 
 -DLINUXV=26032
 -D__BIONIC__
 -DHASIPv6
 -D_FILE_OFFSET_BITS=32 
 -DHAS_STRFTIME 
 -DLSOF_VSTR=\"2.6.32-androidlol\"
)

#static link
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

set(LSOF_SOURCES
 ${PROJECT_SOURCE_DIR}/lsof/lib/ckkv.c
 ${PROJECT_SOURCE_DIR}/lsof/lib/cvfs.c
 ${PROJECT_SOURCE_DIR}/lsof/lib/dvch.c
 ${PROJECT_SOURCE_DIR}/lsof/lib/fino.c
 ${PROJECT_SOURCE_DIR}/lsof/lib/isfn.c
 ${PROJECT_SOURCE_DIR}/lsof/lib/lkud.c
 ${PROJECT_SOURCE_DIR}/lsof/lib/pdvn.c
 ${PROJECT_SOURCE_DIR}/lsof/lib/prfp.c
 ${PROJECT_SOURCE_DIR}/lsof/lib/ptti.c
 ${PROJECT_SOURCE_DIR}/lsof/lib/rdev.c
 ${PROJECT_SOURCE_DIR}/lsof/lib/regex.c
 ${PROJECT_SOURCE_DIR}/lsof/lib/rmnt.c
 ${PROJECT_SOURCE_DIR}/lsof/lib/rnam.c
 ${PROJECT_SOURCE_DIR}/lsof/lib/rnch.c
 ${PROJECT_SOURCE_DIR}/lsof/lib/rnmh.c
 ${PROJECT_SOURCE_DIR}/lsof/lib/snpf.c
 ${PROJECT_SOURCE_DIR}/lsof/dfile.c
 ${PROJECT_SOURCE_DIR}/lsof/dmnt.c
 ${PROJECT_SOURCE_DIR}/lsof/dnode.c
 ${PROJECT_SOURCE_DIR}/lsof/dproc.c
 ${PROJECT_SOURCE_DIR}/lsof/dsock.c
 ${PROJECT_SOURCE_DIR}/lsof/dstore.c
 ${PROJECT_SOURCE_DIR}/lsof/arg.c
 ${PROJECT_SOURCE_DIR}/lsof/main.c
 ${PROJECT_SOURCE_DIR}/lsof/misc.c
 ${PROJECT_SOURCE_DIR}/lsof/node.c
 ${PROJECT_SOURCE_DIR}/lsof/print.c
 ${PROJECT_SOURCE_DIR}/lsof/proc.c
 ${PROJECT_SOURCE_DIR}/lsof/store.c
 ${PROJECT_SOURCE_DIR}/lsof/usage.c
 ${PROJECT_SOURCE_DIR}/lsof/util.c
)

include_directories (${PROJECT_SOURCE_DIR}/../clearsilver/util/regex)
#file(GLOB LSOF_SOURCES "${PROJECT_SOURCE_DIR}/*.c")
add_executable(lsof  ${LSOF_SOURCES})
