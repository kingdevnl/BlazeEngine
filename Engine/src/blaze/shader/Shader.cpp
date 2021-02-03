#include "Shader.h"
#include <iostream>
#include <GL/glew.h>
#include <spdlog/spdlog.h>
#include <glm/gtc/type_ptr.hpp>

namespace Blaze {


    void Shader::Create(const char *vertexSource, const char *fragmentSource) {
        programID = glCreateProgram();
        vertexID = glCreateShader(GL_VERTEX_SHADER);
        fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(vertexID, 1, &vertexSource, nullptr);
        glShaderSource(fragmentID, 1, &fragmentSource, nullptr);

        spdlog::info("{} {} {}", programID, vertexID, fragmentID);

        GLint compileStatus;

        glCompileShader(vertexID);
        glGetShaderiv(vertexID, GL_COMPILE_STATUS, &compileStatus);
        if (!compileStatus) {
            spdlog::error("Failed to compile vertex shader");
            throw "Failed to compile vertex shader";
            exit(1);

        }

        glCompileShader(fragmentID);
        glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &compileStatus);
        if (!compileStatus) {
            spdlog::error("Failed to compile fragment shader");
            throw "Failed to compile fragment shader";
            exit(1);
        }
        glAttachShader(programID, vertexID);
        glAttachShader(programID, fragmentID);
        glLinkProgram(programID);

    }

    void Shader::Bind() {
        glUseProgram(programID);
    }

    void Shader::UploadMat4(std::string name, glm::mat4 value) {
        int location;
        if (!uniformLocations.contains(name)) {
            location = glGetUniformLocation(programID, name.c_str());
            if(location == -1) {
                spdlog::error("Failed to find uniform {}", name);
            }
        } else {
            location = uniformLocations[name];
        }
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));

    }

    void Shader::Unbind() {
        glUseProgram(0);

    }


    void Shader::Destroy() {
        glDetachShader(programID, vertexID);
        glDetachShader(programID, fragmentID);
        glDeleteShader(vertexID);
        glDeleteShader(fragmentID);
        glDeleteProgram(programID);
    }

}