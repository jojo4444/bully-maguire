cmake_minimum_required(VERSION 3.16)

project(generator)

set(SOURCE_EXE main.cpp)

include_directories(../point)

set(GeographicLib_USE_STATIC_LIBS ON) 
find_package(GeographicLib REQUIRED COMPONENTS STATIC)
include_directories(${GeographicLib_INCLUDE_DIRS})

add_library(gen STATIC generator.cpp)

add_executable(generator ${SOURCE_EXE})

target_link_libraries(generator gen point ${GeographicLib_LIBRARIES})
