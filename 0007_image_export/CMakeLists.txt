cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)

project(myProj)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)

find_package(OpenCV REQUIRED)
include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS})

set(SOURCES
   "./main.cpp"
   "./mainwindow.ui"
   "./mainwindow.h"
   "./mainwindow.cpp"
   "./image_export.h"
   "./image_export.cpp"
)

add_executable(myProj WIN32 ${SOURCES})

target_link_libraries(myProj PRIVATE ${OpenCV_LIBS} Qt6::Widgets)