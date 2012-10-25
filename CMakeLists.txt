cmake_minimum_required (VERSION 2.8)
project (DOSTE)

include_directories(${DOSTE_SOURCE_DIR}/core/include)

set(CMAKE_CXX_FLAGS "-g -Wall")

add_subdirectory(core)
add_subdirectory(test)
