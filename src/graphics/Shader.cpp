//
// Created by Issam on 30/12/2025.
//

#include "Shader.h"
#include <cstdio>
#include <fstream>
#include <stdio.h>

namespace Pesto {
    std::string Shader::ReadShader(std::string path){
        FILE *file_ptr;
        #ifdef _WIN32
          fopen_s(&file_ptr, path.c_str(), "r");
        #else
          file_ptr = fopen(path.c_str(), "r");
        #endif // _WIN32
        if(file_ptr == NULL){
            std::cout << "Failed to read shader file " << path << std::endl;
            return "";
        }
        fseek(file_ptr, 0, SEEK_END);
        long size = ftell(file_ptr);
        fseek(file_ptr, 0, SEEK_SET);

        std::string content;
        content.reserve(size);
        char c;
        while((c = fgetc(file_ptr)) != EOF){
            content.push_back(c);
        }
        return content;
    }

    Shader::Shader(const char* vertexPath, const char* fragmentPath){
        std::string vertexSource = ReadShader(vertexPath);
        std::string fragmentSource = ReadShader(fragmentPath);

        if(vertexSource.empty() || fragmentSource.empty()){
            std::cout << "Failed loading shaders"  << std::endl;
            return;
        }

        const char *vertex_char = vertexSource.c_str(), *fragment_char = fragmentSource.c_str();
        GLuint vertexProgram = glCreateShader(GL_VERTEX_SHADER), fragmentProgram = glCreateShader(GL_FRAGMENT_SHADER);
        if(vertexProgram == 0 || fragmentProgram == 0){
            std::cout << "Failed to created shader programs" << std::endl;
            return;
        }

        glShaderSource(vertexProgram, 1, &vertex_char, NULL);
        glCompileShader(vertexProgram);
        // TODO : add shader compile check
        GLint success = 0;
        glGetShaderiv(vertexProgram, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            GLint length = 0;
            glGetShaderiv(vertexProgram, GL_INFO_LOG_LENGTH, &length);
            if (length > 0) {
                char* infoLog = new char[length];
                glGetShaderInfoLog(vertexProgram, length, &length, infoLog);
                std::cout << "VERTEX SHADER COMPILATION ERROR:" << infoLog;
                delete[] infoLog;
            }
            glDeleteShader(vertexProgram);
            glDeleteShader(fragmentProgram);
            return;
        }


        glShaderSource(fragmentProgram, 1, &fragment_char, NULL);
        glCompileShader(fragmentProgram);
        success = 0;
        glGetShaderiv(fragmentProgram, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            GLint length = 0;
            glGetShaderiv(fragmentProgram, GL_INFO_LOG_LENGTH, &length);
            if (length > 0) {
                char* infoLog = new char[length];
                glGetShaderInfoLog(fragmentProgram, length, &length, infoLog);
                std::cout << "VERTEX SHADER COMPILATION ERROR:" << infoLog;
                delete[] infoLog;
            }
            glDeleteShader(vertexProgram);
            glDeleteShader(fragmentProgram);
            return;
        }


        m_shaderProgram = glCreateProgram();
        glAttachShader(m_shaderProgram, vertexProgram);
        glAttachShader(m_shaderProgram, fragmentProgram);

        glDeleteShader(vertexProgram);
        glDeleteShader(fragmentProgram);

        glLinkProgram(m_shaderProgram);
    }

    Shader::~Shader(){
        glDeleteProgram(m_shaderProgram);
    }

    void Shader::EnableShader(){
        glUseProgram(m_shaderProgram);
    }

    void Shader::DisableShader(){
        glUseProgram(0);
    }

    GLuint Shader::GetShaderID() const {
        return m_shaderProgram;
    }

    GLint Shader::GetUniformLoc(const GLchar *name) const {
        return glGetUniformLocation(m_shaderProgram, name);
    }


    void Shader::SetUniform1f(const GLchar *name, float val){
        GLint location = GetUniformLoc(name);
        glUniform1f(location, val);
    }

    void Shader::SetUniform2f(const GLchar *name, GeoMa::Vector2F vec){
        GLint location = GetUniformLoc(name);
        glUniform2f(location, vec.x, vec.y);
    }

    void Shader::SetUniform3f(const GLchar *name, GeoMa::Vector3F vec){
        GLint location = GetUniformLoc(name);
        glUniform3f(location, vec.x, vec.y, vec.z);
    }

    void Shader::SetUniform4f(const GLchar *name, GeoMa::Vector4F vec){
        GLint location = GetUniformLoc(name);
        glUniform4f(location, vec.x, vec.y, vec.z, vec.t);
    }

    void Shader::SetUniform1i(const GLchar *name, int val){
        GLint location = GetUniformLoc(name);
        glUniform1i(location, val);
    }

    void Shader::SetUniform2i(const GLchar *name, GeoMa::Vector2I vec){
        GLint location = GetUniformLoc(name);
        glUniform2i(location, vec.x, vec.y);
    }

    void Shader::SetUniform3i(const GLchar *name, GeoMa::Vector3I vec){
        GLint location = GetUniformLoc(name);
        glUniform3i(location, vec.x, vec.y, vec.z);
    }

    void Shader::SetUniform4i(const GLchar *name, GeoMa::Vector4I vec){
        GLint location = GetUniformLoc(name);
        glUniform4i(location, vec.x, vec.y, vec.z, vec.t);
    }

    void Shader::SetUniformMat4(const GLchar* name, GeoMa::Matrix4F mat) {
        GLint location = GetUniformLoc(name);
        float floatData[16];
        for (int i = 0; i < 16; i++) {
            floatData[i] = static_cast<float>(mat[i]);
        }
        glUniformMatrix4fv(location, 1, GL_FALSE, floatData);
    }

}
