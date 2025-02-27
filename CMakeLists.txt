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
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

find_package(pybind11 CONFIG REQUIRED)
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
        TriEngine/engine/core/Window.h
        TriEngine/engine/utility/Image.cpp
        TriEngine/engine/utility/Image.h
        TriEngine/engine/core/GameManager.cpp
        TriEngine/engine/core/GameManager.h
        TriEngine/engine/py/APyManager.cpp
        TriEngine/engine/py/APyManager.h
        TriEngine/engine/py/APyInterp.cpp
        TriEngine/engine/py/APyInterp.h
        TriEngine/engine/core/Engine.cpp
        TriEngine/engine/core/Engine.h
        TriEngine/engine/core/PyCore.cpp
        TriEngine/engine/core/PyCore.h
        TriEngine/engine/common/EventDispatcher.h
        TriEngine/engine/ecs/systems/Renderer.cpp
        TriEngine/engine/ecs/systems/Renderer.h
        TriEngine/engine/ecs/components/ChildrenComponent.cpp
        TriEngine/engine/ecs/components/ChildrenComponent.h
        TriEngine/engine/ecs/components/IComponent.h
        TriEngine/engine/ecs/entities/IActor.h
)

target_include_directories(TriEngine PUBLIC
        ${Stb_INCLUDE_DIR}
        ${Python3_INCLUDE_DIRS}
)

target_link_libraries(TriEngine
        OpenGL::GL
        glm::glm
        glad::glad
        imgui::imgui
        glfw
        pybind11::module
        ${Python3_LIBRARIES}
)