cmake_minimum_required(VERSION 3.21)
project(server)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall )
add_link_options(-pthread)

add_executable(server src/main.cpp)
