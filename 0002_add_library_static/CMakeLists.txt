cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

project(myApp)

add_library(myLib add.h add.cpp)

add_executable(myApp main.cpp)

target_link_libraries(myApp PRIVATE myLib)