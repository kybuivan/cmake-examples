cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)

project(myProj)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

add_library(myDLL SHARED add.h add.cpp)

add_executable(myProj main.cpp)

target_link_libraries(myProj PUBLIC myDLL)