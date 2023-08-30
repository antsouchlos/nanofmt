add_executable(nanofmt_example src/example.cpp)
target_link_libraries(nanofmt_example nanofmt)

if(MSVC)
    target_compile_options(nanofmt_example PRIVATE /W4 /WX)
else()
    target_compile_options(nanofmt_example PRIVATE -O3 -Wall -Wextra -pedantic -fno-exceptions)
endif()