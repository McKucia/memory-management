cmake_minimum_required(VERSION 3.17)
project(shared_ptr)

set(CMAKE_CXX_STANDARD 17)

add_executable(shared_ptr main.cpp main.cpp NullPtrException.h)