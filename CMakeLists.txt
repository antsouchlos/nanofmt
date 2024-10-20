cmake_minimum_required(VERSION 3.21)
project(nanofmt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_library(nanofmt src/serialize.cpp)
target_include_directories(nanofmt PUBLIC include)

if(PROJECT_IS_TOP_LEVEL)
    #
    # Build as standalone project
    #

    option(PACKAGE_TESTS "Build the tests" ON)
    if(PACKAGE_TESTS)
        enable_testing()
        include(GoogleTest)
        add_subdirectory(test)
    endif()

    add_subdirectory(examples)
endif()
