cmake_minimum_required(VERSION 3.10)
project(test)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)

add_library(GLFW STATIC IMPORTED)

set_target_properties(GLFW PROPERTIES
INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/"
IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/glfw3.lib"
)

add_executable(test main.cpp)

target_link_libraries(test GLFW OpenGL::GL)
