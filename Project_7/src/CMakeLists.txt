cmake_minimum_required(VERSION 3.10)
project(src)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(src STATIC indexBuffer.cpp Renderer.cpp VertexBuffer.cpp VertexArray.cpp Shader.cpp Texture.cpp stb_image.cpp)

find_package(OpenGL REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/glm)

add_library(GLEW STATIC IMPORTED)
set_target_properties(GLEW PROPERTIES
INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/GLEW/include/"
IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/GLEW/glew32s.lib"
)
target_compile_definitions(GLEW INTERFACE GLEW_STATIC)

add_library(GLFW STATIC IMPORTED)
set_target_properties(GLFW PROPERTIES
INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/GLFW/include/"
IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/GLFW/glfw3.lib"
)

target_include_directories(src PUBLIC "./")
target_link_libraries(src PUBLIC GLEW GLFW OpenGL::GL glm::glm)


