//
// Created by Issam on 30/12/2025.
//

#ifndef PESTO3D_SHADER_H
#define PESTO3D_SHADER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../math/GeoMa.h"

namespace Pesto {
    class Shader {
    private:
        GLuint      m_shaderProgram;
        const char  *m_vertexPath, *m_fragmentPath;

        std::string ReadShader(std::string path);
    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();

        void        EnableShader();
        void        DisableShader();
        GLuint      GetShaderID() const;
        GLint       GetUniformLoc(const GLchar *name) const;


        void        SetUniform1f(const GLchar* name, float val);
        void        SetUniform2f(const GLchar* name, GeoMa::Vector2F vec);
        void        SetUniform3f(const GLchar* name, GeoMa::Vector3F vec);
        void        SetUniform4f(const GLchar* name, GeoMa::Vector4F vec);
        void        SetUniform1i(const GLchar* name, int val);
        void        SetUniform2i(const GLchar* name, GeoMa::Vector2I vec);
        void        SetUniform3i(const GLchar* name, GeoMa::Vector3I vec);
        void        SetUniform4i(const GLchar* name, GeoMa::Vector4I vec);

    };
}


#endif //PESTO3D_SHADER_H