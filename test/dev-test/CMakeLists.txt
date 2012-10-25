include_directories(${DOSTE_SOURCE_DIR}/test/dev-test)
link_directories(${DOSTE_BINARY_DIR}/core)

set(SOURCEFILES dev-test.cpp)

add_executable(dev-test ${SOURCEFILES})
target_link_libraries(dev-test doste)
