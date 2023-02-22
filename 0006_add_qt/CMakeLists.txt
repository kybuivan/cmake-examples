cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)

project(myProj)

set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo" CACHE STRING "" FORCE)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)

set(SOURCES
   "./main.cpp"
   "./mainwindow.ui"
   "./mainwindow.h"
   "./mainwindow.cpp"
)

#set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(myProj WIN32 ${SOURCES})

target_link_libraries(myProj Qt6::Widgets)