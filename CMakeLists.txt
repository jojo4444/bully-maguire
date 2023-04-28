cmake_minimum_required(VERSION 3.16)
SET(CMAKE_SUPPRESS_REGENERATION TRUE)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -pedantic")

project(bully-maguire)

add_subdirectory(generator)

add_subdirectory(solution)

add_subdirectory(point)
