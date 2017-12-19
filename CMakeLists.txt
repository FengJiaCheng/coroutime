cmake_minimum_required(VERSION 3.9)
project(coroutime)

set(CMAKE_CXX_STANDARD 11)

add_executable(coroutime main.cpp coro.cpp coro.h )