//
// Created by Issam on 30/12/2025.
//

#ifndef PESTO3D_INDEXBUFFER_H
#define PESTO3D_INDEXBUFFER_H
#include "iBuffer.h"
#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace Pesto{
    class IndexBuffer : iBuffer{
    private:
        unsigned int m_count;
    public:
        IndexBuffer(GLuint *indices, unsigned int count);
        ~IndexBuffer();

        void Bind() override;
        void Unbind() override;
        inline unsigned int GetCount(){return m_count;}
    };
}

#endif //PESTO3D_INDEXBUFFER_H