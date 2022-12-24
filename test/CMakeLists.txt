cmake_minimum_required(VERSION 3.16)

project(test)

set(SOURCE_EXE main.cpp)

include_directories(../point)

add_library(tester STATIC tester.cpp)

add_executable(test ${SOURCE_EXE})

target_link_libraries(test tester point)
