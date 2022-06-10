file(GLOB_RECURSE SRC_LIST "*.cpp" "*.cc" )
file(GLOB_RECURSE HEAD_LIST "*.h")
message(STATUS "source list :" ${SRC_LIST})
message(STATUS "header list :" ${HEAD_LIST})

add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEAD_LIST})

target_link_libraries(${PROJECT_NAME}
        ${THIRD_PARTY_LIB_LIST})
