set(SOURCEFILES dsbd.cpp server.cpp rpc.cpp)

add_executable(dsbd ${SOURCEFILES})
target_link_libraries(dsbd dsb)