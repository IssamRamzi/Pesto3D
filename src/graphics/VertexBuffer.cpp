//
// Created by Issam on 30/12/2025.
//

#include "VertexBuffer.h"

namespace Pesto{

    VertexBuffer::VertexBuffer(){
        glGenBuffers(1, &m_bufferID);
    }

    VertexBuffer::VertexBuffer(GLfloat* vertices, int countComponents, int countElements) : m_countComponents(countComponents), m_countElements(countElements) {
        glGenBuffers(1, &m_bufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
        glBufferData(GL_ARRAY_BUFFER, countElements * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    VertexBuffer::~VertexBuffer(){
        glDeleteBuffers(1, &m_bufferID);
    }

    void VertexBuffer::Bind(){
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
    }

    void VertexBuffer::Unbind(){
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::SetData(GLfloat* vertices, int countComponents, size_t countElements){
        m_countComponents = countComponents , m_countElements =countElements;
        Bind();
        glBufferData(GL_ARRAY_BUFFER, countElements * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
        Unbind();
    }

}