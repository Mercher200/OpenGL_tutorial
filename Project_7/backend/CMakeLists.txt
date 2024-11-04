cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

add_library(backend STATIC imgui_impl_glfw.cpp imgui_impl_glfw.h imgui_impl_opengl3.cpp imgui_impl_opengl3.h imgui_impl_opengl3_loader.h)

find_package(OpenGL REQUIRED)

add_library(GLFW STATIC IMPORTED)

set_target_properties(GLFW PROPERTIES
INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/GLFW/include/"
IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/GLFW/glfw3.lib"
)

target_include_directories(backend PUBLIC "./")
target_link_libraries(backend PUBLIC OpenGL::GL GLFW imgui)