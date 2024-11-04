cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

add_library(imgui STATIC imgui_demo.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp imgui.cpp)

find_package(OpenGL REQUIRED)

target_include_directories(imgui PUBLIC "./")
target_link_libraries(imgui PUBLIC OpenGL::GL)

