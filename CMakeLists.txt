cmake_minimum_required(VERSION 3.16...3.30)

project(ccc CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

set(PROGRAMS
        hello
        cond
        )

foreach (program ${PROGRAMS})
    add_executable(${program} ${program}.cc)
    if (MSVC)
        target_compile_options(${program} PRIVATE /W4)
    else ()
        target_compile_options(${program} PRIVATE -Wall -Wextra -pedantic)
    endif ()
    add_test(NAME ${program} COMMAND ${program})
endforeach (program)
