cmake_minimum_required(VERSION 3.16)

project(solution)

set(SOURCE_EXE main.cpp)

include_directories(../point)

add_library(sol STATIC solution.cpp)

add_executable(solution ${SOURCE_EXE})

target_link_libraries(solution sol point)
