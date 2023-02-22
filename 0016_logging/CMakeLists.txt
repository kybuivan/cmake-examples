cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

project(myProj)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${PROJECT_SOURCE_DIR}/cmake/external)
include(FetchContent)
include(fmt)
include(spdlog)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt spdlog::spdlog)