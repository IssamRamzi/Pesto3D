//
// Created by Issam on 30/12/2025.
//

#ifndef PESTO3D_VERTEXBUFFER_H
#define PESTO3D_VERTEXBUFFER_H
#include "iBuffer.h"
#include "glad/glad.h"
#include "glfw/glfw3.h"


namespace Pesto{
    class VertexBuffer : iBuffer{
    private:
        int m_countComponents, m_countElements;
    public:
        VertexBuffer();
        VertexBuffer(GLfloat* vertices, int countComponents, int countElements);
        ~VertexBuffer();

        void SetData(GLfloat* vertices, int countComponents, size_t countElements);

        void Bind() override;
        void Unbind() override;
    };
}


#endif //PESTO3D_VERTEXBUFFER_H