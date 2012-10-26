cmake_minimum_required (VERSION 2.8)
project (DSB)

include_directories(${DSB_SOURCE_DIR}/api/cpp/include)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++0x")

add_subdirectory(api)
add_subdirectory(core)
add_subdirectory(test)
