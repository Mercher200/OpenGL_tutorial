cmake_minimum_required(VERSION 3.10)
project(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

add_executable(test main.cpp)

target_link_libraries(test PUBLIC OpenGL::GL src)
