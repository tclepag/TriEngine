//
// Created by lepag on 2/16/2025.
//

#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>
#include <stdexcept>

#include <glad/glad.h>
#include <glm/fwd.hpp>

#include "../util/File.h"


namespace tri::graphics {
    inline auto FALLBACK_FRAGMENT = "content/shaders/default.frag";

class ShaderProgram {
    public:
        const GLuint id;

        ShaderProgram(const char* vertexPath, const char* fragmentPath);
        ~ShaderProgram();

        // Sets the new file path for vertex shader and fragment
        bool context(const char* vertexPath = nullptr, const char* fragmentPath = nullptr);
        // Get uniform location
        GLint uniform(const char* uniformName) const;
        // Sets uniform mat4
        void uniformMat4(const char* uniformName, glm::mat4& matrix) const;
        // Sets uniform float
        void uniformFloat(const char* uniformName, float value) const;
        // Sets uniform int
        void uniformInt(const char* uniformName, int value) const;
        // Set uniform vec2
        void uniformVec2(const char *uniformName, float x, float y) const;
        // Set uniform vec3
        void uniformVec3(const char *uniformName, float x, float y, float z) const;
        // Set uniform vec4
        void uniformVec4(const char *uniformName, float x, float y, float z, float w) const;
        // Set uniform mat3
        void uniformMat3(const char* uniformName, glm::mat3& matrix) const;


        // Links this shader's program
        void use() const;
        // Compiles vertex and fragment shaders
        // If these shaders exist already, deletes and recompiles
        void compile();
        // Destroys the shader
        void free() const;
        // Create Shader
        static GLuint createShader(const char *path, GLenum shaderType);
protected:
    const char* vertexShaderSource;
    const char* fragmentShaderSource;

        GLuint vertexShader{};
        GLuint fragmentShader{};
};

} // graphics
// tri

#endif //SHADER_HPP
