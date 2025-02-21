cmake_minimum_required(VERSION 3.30)

project(TriEngine)

set(CMAKE_TOOLCHAIN_FILE  "$ENV{VCPKG_ROOT}")

# Build Settings
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/TriEngine)

file(COPY "${CMAKE_SOURCE_DIR}/TriEngine/content/" DESTINATION "${OUTPUT_DIR}/content")
file(COPY "${CMAKE_SOURCE_DIR}/TriEngine/engine/" DESTINATION "${OUTPUT_DIR}/engine")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}")

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(imgui REQUIRED)

add_executable(TriEngine main.cpp
        TriEngine/engine/buffers/VertexArrayObject.h
        TriEngine/engine/buffers/VertexBufferObject.h
        TriEngine/engine/buffers/ElementBufferObject.h
        TriEngine/engine/buffers/FrameBufferObject.h
        TriEngine/engine/core/Window.cpp
        TriEngine/engine/core/Window.h)

target_include_directories(TriEngine PUBLIC
        ${Stb_INCLUDE_DIR}
)

target_link_libraries(TriEngine
        OpenGL::OpenGL
        glm::glm
        glad::glad
        imgui::imgui
        glfw
)