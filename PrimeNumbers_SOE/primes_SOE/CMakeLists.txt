cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(primes_SOE)

add_executable(
primes_SOE
main.cpp
)