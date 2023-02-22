cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

project(myProj)

set(src_files
    main.cpp)

#add_executable(${PROJECT_NAME} ${src_files})

#opengl
find_package(OpenGL REQUIRED)

if (NOT freeglutgit_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    freeglut
    URL  https://github.com/FreeGLUTProject/freeglut/releases/download/v3.2.2/freeglut-3.2.2.tar.gz
    )
  FetchContent_MakeAvailable(freeglut)
  if(NOT TARGET freeglut::freeglut)
    if (TARGET freeglut_static)
        add_library(freeglut::freeglut ALIAS freeglut_static)
        target_include_directories(freeglut_static INTERFACE $<BUILD_INTERFACE:${freeglut_SOURCE_DIR}/include>)
    elseif (TARGET freeglut)
        add_library(freeglut::freeglut ALIAS freeglut)
        target_include_directories(freeglut INTERFACE $<BUILD_INTERFACE:${freeglut_SOURCE_DIR}/include>)
    endif ()
  endif ()
endif()

include_directories( ${OPENGL_INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES} freeglut::freeglut)

add_executable(example
#  examples/double.c
#  examples/lines.c
#  examples/polys.c
  examples/varray.c)

target_link_libraries(example PRIVATE ${OPENGL_LIBRARIES} freeglut::freeglut)

