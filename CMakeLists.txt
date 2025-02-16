cmake_minimum_required(VERSION 3.30)

project(TriEngine)

set(CMAKE_TOOLCHAIN_FILE  "C:/Users/lepag/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Build Settings
set(LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/TriEngine")
set(RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/TriEngine")
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/TriEngine")
file(COPY "${CMAKE_SOURCE_DIR}/TriEngine/content/" DESTINATION "${OUTPUT_DIR}/content")
file(COPY "${CMAKE_SOURCE_DIR}/TriEngine/scripts/" DESTINATION "${OUTPUT_DIR}/scripts")


set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_executable(TriEngine main.cpp)

target_include_directories(TriEngine PUBLIC
        ${Stb_INCLUDE_DIR}
)

target_link_libraries(TriEngine
        OpenGL::GL
        glfw
        glm::glm
        glad::glad
)