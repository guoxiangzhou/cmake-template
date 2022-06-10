project(demo LANGUAGES CXX)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_C_COMPILER "/usr/local/bin/gcc")
#set(CMAKE_CXX_COMPILER "/usr/local/bin/g++")

IF (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
        "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
ENDIF()

message(STATUS "build type : " ${CMAKE_BUILD_TYPE})

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/dist/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH ${CMAKE_INSTALL_PREFIX}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_INSTALL_PREFIX}/bin)

file(MAKE_DIRECTORY ${LIBRARY_OUTPUT_PATH})
file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})


option(BUILD_UNIT_TEST "build unit test" OFF)
option(BUILD_WITH_GPU "build with gpu" OFF)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Xpreprocessor -fopenmp -fPIC")


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(THIRD_PARTY_LIB_LIST
        event
        pthread
        c)

add_subdirectory(src)

if (BUILD_UNIT_TEST)
    add_subdirectory(unittest)
endif ()

