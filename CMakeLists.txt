cmake_minimum_required(VERSION 3.10)

project(ccc CXX)

set (CMAKE_CXX_STANDARD 17)
if (NOT MSVC)
  set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
endif()

set(PROGRAMS
    hello
    )

find_package(Threads REQUIRED)

foreach(program ${PROGRAMS})
  add_executable(${program} ${program}.cc)
  target_link_libraries(${program} ${CORELIBS} ${CMAKE_THREAD_LIBS_INIT})
endforeach(program)
