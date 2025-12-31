//
// Created by Issam on 30/12/2025.
//

#include "IndexBuffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace Pesto{
IndexBuffer::IndexBuffer(GLuint *indices, unsigned int count) : m_count(count){
    glGenBuffers(1, &m_bufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer(){
    glDeleteBuffers(1, &m_bufferID);
}

void IndexBuffer::Bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
}

void IndexBuffer::Unbind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}