include_directories(${DSB_SOURCE_DIR}/test/dev-test)
link_directories(${DSB_BINARY_DIR}/core)

set(SOURCEFILES dev-test.cpp)

add_executable(dev-test ${SOURCEFILES})
target_link_libraries(dev-test dsb)
