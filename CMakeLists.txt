cmake_minimum_required(VERSION 3.17)
project(Pangolins C)
find_package(Threads REQUIRED)

set(CMAKE_C_STANDARD 11)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(Pangolins main.c common_defs.h globals.h queue.c queue.h)
target_link_libraries(Pangolins pthread)