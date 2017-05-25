cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

option(RPATH "Hack rpath to $ORIGIN/libs" OFF)
if(RPATH)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,$ORIGIN/libs")
endif()

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS} "utfcpp")

include_directories(${CMAKE_CURRENT_BINARY_DIR})
PROTOBUF_GENERATE_CPP(PROTO1_SRCS PROTO1_HDRS
    src/netmessages.proto
    src/steammessages.proto
    src/cstrike15_gcmessages.proto
    src/cstrike15_usermessages.proto)

find_package(JsonSpirit REQUIRED)
include_directories(${JSON_SPIRIT_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x")
add_executable(demoinfogo
    src/geometry.cpp
    src/demofile.cpp
    src/demofiledump.cpp
    src/demoinfogo.cpp
    src/demofilebitbuf.cpp
    src/demofilepropdecode.cpp
    ${PROTO1_SRCS} ${PROTO1_HDRS}
    ${PROTO2_SRCS} ${PROTO2_HDRS})
target_link_libraries(demoinfogo ${PROTOBUF_LIBRARIES} ${JSON_SPIRIT_LIBRARY})

