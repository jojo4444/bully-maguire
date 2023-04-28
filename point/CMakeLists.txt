cmake_minimum_required(VERSION 3.16)

project(point)

set(GeographicLib_USE_STATIC_LIBS ON) 
find_package(GeographicLib REQUIRED COMPONENTS STATIC)
include_directories(${GeographicLib_INCLUDE_DIRS})

add_library(point STATIC point.cpp)

target_link_libraries(point ${GeographicLib_LIBRARIES})
