cmake_minimum_required(VERSION 3.21.0)
project(bufferTool)

set(CMAKE_CXX_STANDARD 11)


INCLUDE_DIRECTORIES(../include/)

add_executable(bufferTool src/main.cpp)
