cmake_minimum_required(VERSION 3.10.2)

project(primes_mul)

#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -pthread")
list(APPEND CMAKE_CXX_FLAGS "-std=c++14")

find_package (Threads)
add_executable (
main main.cpp
)
target_link_libraries(main Threads::Threads)

# g++ -c main.cpp -o main.o -pthread
# g++ -pthread main.o main
