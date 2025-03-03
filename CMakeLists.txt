cmake_minimum_required(VERSION 3.30)

project(TriEngine)

set(CMAKE_TOOLCHAIN_FILE  "$ENV{VCPKG_ROOT}")

# Build Settings
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/TriEngine)

file(COPY "${CMAKE_SOURCE_DIR}/TriEngine/content/" DESTINATION "${OUTPUT_DIR}/content")
file(COPY "${CMAKE_SOURCE_DIR}/TriEngine/scripts/" DESTINATION "${OUTPUT_DIR}/scripts")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}")

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glad REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(imgui REQUIRED)

add_executable(TriEngine main.cpp
        TriEngine/scripts/core/Screen.cpp
        TriEngine/scripts/core/Screen.h
        TriEngine/scripts/util/Image.cpp
        TriEngine/scripts/util/Image.h
        TriEngine/scripts/graphics/Shader.cpp
        TriEngine/scripts/graphics/Shader.h
        TriEngine/scripts/util/File.cpp
        TriEngine/scripts/util/File.h
        TriEngine/scripts/classes/Actor.cpp
        TriEngine/scripts/classes/Actor.h
        TriEngine/scripts/graphics/ObjectBuffer.cpp
        TriEngine/scripts/graphics/ObjectBuffer.h
        TriEngine/scripts/classes/components/ActorComponent.cpp
        TriEngine/scripts/classes/components/ActorComponent.h
        TriEngine/scripts/classes/components/Mesh.cpp
        TriEngine/scripts/classes/components/Mesh.h
        TriEngine/scripts/util/Time.cpp
        TriEngine/scripts/util/Time.h
        TriEngine/scripts/graphics/GLRenderer.cpp
        TriEngine/scripts/graphics/GLRenderer.h
        TriEngine/scripts/buffers/VertexArrayObject.h
        TriEngine/scripts/buffers/VertexBufferObject.h
        TriEngine/scripts/buffers/ElementBufferObject.h
        TriEngine/scripts/buffers/FrameBufferObject.h
        TriEngine/scripts/graphics/textures/BaseTextureClass.cpp
        TriEngine/scripts/graphics/textures/BaseTextureClass.h
        TriEngine/scripts/graphics/textures/Texture2D.cpp
        TriEngine/scripts/graphics/textures/Texture2D.h
        TriEngine/scripts/graphics/textures/Texture3D.cpp
        TriEngine/scripts/graphics/textures/Texture3D.h)

target_include_directories(TriEngine PUBLIC
        ${Stb_INCLUDE_DIR}
)

target_link_libraries(TriEngine
        opengl32
        glm::glm
        glad::glad
        imgui::imgui
)

set_target_properties(TriEngine PROPERTIES
        WIN32_EXECUTABLE YES
)