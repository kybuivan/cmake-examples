cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

project(myProj)

find_package(OpenCV REQUIRED)
include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS})

add_executable(myProj main.cpp)
target_link_libraries(myProj PRIVATE ${OpenCV_LIBS})