//
// Created by lepag on 2/16/2025.
//

#include "Shader.hpp"

#include <glm/gtc/type_ptr.hpp>


namespace tri::graphics {
    ShaderProgram::ShaderProgram(const char *vertexPath, const char *fragmentPath): id(glCreateProgram()) {
        vertexShaderSource = vertexPath;
        fragmentShaderSource = fragmentPath;
        compile();
    }

    ShaderProgram::~ShaderProgram() {
        if (fragmentShader != 0) {
            glDeleteShader(fragmentShader);
        }
        if (vertexShader != 0) {
            glDeleteShader(vertexShader);
        }
        glDeleteProgram(id);
    }

    void ShaderProgram::free() const {
        this->~ShaderProgram();
    }


    void ShaderProgram::use() const {
        glUseProgram(id);
    }

    void ShaderProgram::compile() {
        vertexShader = createShader(vertexShaderSource, GL_VERTEX_SHADER);
        fragmentShader = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
        if (!fragmentShader) {
            std::cerr << "Error creating fragment shader" << std::endl;
            fragmentShader = createShader("content/shaders/default.frag", GL_FRAGMENT_SHADER);
        }

        GLint success;
        char infoLog[512];

        glAttachShader(id, vertexShader);
        glAttachShader(id, fragmentShader);
        glLinkProgram(id);

        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            std::cerr << "Error linking program" << std::endl;
            std::cerr << infoLog << std::endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        use();
    }

    GLint ShaderProgram::uniform(const char *uniformName) {
        GLint location = glGetUniformLocation(id, uniformName);
        if (location == -1) {
            std::cerr << "Error getting uniform location." << "Using program ID" << id << std::endl;
            std::cerr << uniformName << std::endl;
        }
        return location;
    }


    void ShaderProgram::uniformFloat(const char *uniformName, float value) {
        glUniform1f(uniform(uniformName), value);
    }

    void ShaderProgram::uniformInt(const char *uniformName, int value) {
        glUniform1i(uniform(uniformName), value);
    }

    void ShaderProgram::uniformVec2(const char *uniformName, const float x, const float y) {
        glUniform2f(uniform(uniformName), x, y);
    }

    void ShaderProgram::uniformVec3(const char *uniformName, const float x, const float y, const float z) {
        glUniform3f(uniform(uniformName), x, y, z);
    }

    void ShaderProgram::uniformVec4(const char *uniformName, const float x, const float y, const float z, const float w) {
        glUniform4f(uniform(uniformName), x, y, z, w);
    }

    void ShaderProgram::uniformMat4(const char *uniformName, glm::mat4 &matrix) {
        glUniformMatrix4fv(uniform(uniformName), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void ShaderProgram::uniformMat3(const char *uniformName, glm::mat3 &matrix) {
        glUniformMatrix3fv(uniform(uniformName), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    GLuint ShaderProgram::createShader(const char *path, GLenum shaderType) {
        std::string shaderCode = util::File::fileToString(path);
        const char* shaderStringCode = shaderCode.c_str();
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderStringCode, nullptr);
        glCompileShader(shader);

        GLint success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);

            if (shaderType == GL_VERTEX_SHADER) {
                std::cerr << "Vertex shader compile failure" << std::endl;
            } else {
                std::cerr << "Fragment compile failure" << std::endl;
            }

            std::cerr << infoLog << std::endl;
            glDeleteShader(shader);
        }

        return shader;
    }


} // graphics
// tri