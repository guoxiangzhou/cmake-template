file(GLOB_RECURSE SRC_LIST "*.cpp" "*.cc" )
file(GLOB_RECURSE HEAD_LIST "*.h")
message(STATUS "source list :" ${SRC_LIST})
message(STATUS "header list :" ${HEAD_LIST})

add_executable(server ${SRC_LIST} ${HEAD_LIST})

target_link_libraries(server
        ${THIRD_PARTY_LIB_LIST})
