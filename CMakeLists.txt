cmake_minimum_required(VERSION 3.21)
project(nanofmt)

set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_library(nanofmt src/serialize.cpp)
target_include_directories(nanofmt PUBLIC include)

get_directory_property(hasParent PARENT_DIRECTORY)
if(!hasParent)
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
