cmake_minimum_required(VERSION 3.6)
project(dp_poly)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(dp_poly ${SOURCE_FILES})
