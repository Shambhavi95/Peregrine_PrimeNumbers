cmake_minimum_required(VERSION 3.10.2)

project(primes_mul)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -pthread")

find_package (Threads)
add_executable (
main main.cpp
)
target_link_libraries (main ${CMAKE_THREAD_LIBS_INIT})