//
// Created by Issam on 30/12/2025.
//

#include "VertexArrays.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"

namespace Pesto{
    VertexArrays::VertexArrays(){
        glGenVertexArrays(1, &m_bufferID);
    }

    VertexArrays::~VertexArrays(){
        glDeleteVertexArrays(1, &m_bufferID);
    }

    void VertexArrays::Bind(){
        glBindVertexArray(m_bufferID);
    }

    void VertexArrays::Unbind(){
        glBindVertexArray(0);
    }

    void VertexArrays::AddBuffer(VertexBuffer& buffer, unsigned int index, unsigned int componentsCount, int stride, void *offset){
        Bind();
        buffer.Bind();
        glVertexAttribPointer(index, componentsCount, GL_FLOAT, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(index);
    }
}
