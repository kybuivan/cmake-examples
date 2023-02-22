cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

project(myProj)

set(src_files
    main.cpp
    )

add_executable(${PROJECT_NAME} ${src_files})

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
    add_library(freeglut::freeglut ALIAS freeglut)
    target_include_directories(freeglut INTERFACE $<BUILD_INTERFACE:${freeglut_SOURCE_DIR}/include>)
  endif ()
  include_directories($<BUILD_INTERFACE:${freeglut_SOURCE_DIR}/include>)
endif()

include_directories( ${OPENGL_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/external/glm/include
    ${PROJECT_SOURCE_DIR}/external/imgui/include
    ${PROJECT_SOURCE_DIR}/external/stb/include)

# imgui
add_subdirectory(external/imgui EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui)

# stb
add_subdirectory(external/stb EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} PRIVATE stb)

target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES} freeglut::freeglut)