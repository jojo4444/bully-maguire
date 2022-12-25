cmake_minimum_required(VERSION 3.16)

project(generator)

set(SOURCE_EXE main.cpp)

include_directories(../point)

add_library(gen STATIC generator.cpp)

add_executable(generator ${SOURCE_EXE})

target_link_libraries(generator gen point)
