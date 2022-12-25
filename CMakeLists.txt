cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_RELEASE "-O2")

project(bully-maguire)

add_subdirectory(generator)

add_subdirectory(solution)

add_subdirectory(point)
