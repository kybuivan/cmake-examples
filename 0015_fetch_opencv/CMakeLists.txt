cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

project(myProj)

#find_package(OpenCV REQUIRED)
# External dependencies
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${PROJECT_SOURCE_DIR}/cmake/external)
include(FetchContent)
include(opencv)
#include(googletest)
#include(boost)
include(nfd)
include(imgui)

include_directories(SYSTEM ${opencv_INCLUDE_DIRS})

add_executable(myProj main.cpp App.cpp)
target_link_libraries(myProj PRIVATE imgui::imgui ${opencv_LIBS} nfd)