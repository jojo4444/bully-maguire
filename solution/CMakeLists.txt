cmake_minimum_required(VERSION 3.16)

project(solution)

set(SOURCE_EXE main.cpp)
set(SOURCE_SHARED solutionExternal.cpp)

include_directories(../point)

set(GeographicLib_USE_STATIC_LIBS ON) 
find_package(GeographicLib REQUIRED COMPONENTS STATIC)
include_directories(${GeographicLib_INCLUDE_DIRS})

add_library(sol STATIC 
    solutionSphere.cpp 
    solutionGeoid.cpp
    solutionAstronomicalSphere.cpp
)

if(NOT UNIX)
    add_library(solextr SHARED ${SOURCE_SHARED})
    target_link_libraries(solextr sol point ${GeographicLib_LIBRARIES})
endif()

add_executable(solution ${SOURCE_EXE})

target_link_libraries(solution sol point ${GeographicLib_LIBRARIES})
