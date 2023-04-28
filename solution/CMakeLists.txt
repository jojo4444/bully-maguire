cmake_minimum_required(VERSION 3.16)

project(solution)

set(SOURCE_EXE main.cpp)

include_directories(../point)

find_package (GeographicLib REQUIRED)
include_directories (${GeographicLib_INCLUDE_DIRS})

add_library(sol STATIC solutionSphere.cpp)

add_executable(solution ${SOURCE_EXE})

target_link_libraries(solution sol point ${GeographicLib_LIBRARIES})
