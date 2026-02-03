//
// Created by Issam on 26/01/2026.
//

#include "FrameBuffer.h"

#include <iostream>
#include <ostream>

namespace Pesto {
    FrameBuffer::FrameBuffer(f32 width, f32 height, bool useHdr) :_useHdr(useHdr) {
        glGenFramebuffers(1, &m_bufferID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_bufferID);

        // texture Attachment
        glGenTextures(1, &m_ColorTexture);
        glBindTexture(GL_TEXTURE_2D, m_ColorTexture);
        if (_useHdr) {
            std::cout << "Using hdr texture" << std::endl;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorTexture, 0);

        // Renderbuffer for Depth/Stencil
        glGenRenderbuffers(1, &m_RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

        Unbind();
    }

    FrameBuffer::~FrameBuffer() {
        glDeleteFramebuffers(1, &m_bufferID);
        glDeleteTextures(1, &m_ColorTexture);
        glDeleteRenderbuffers(1, &m_RBO);
    }

    void FrameBuffer::Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_bufferID);
    }

    void FrameBuffer::BindTexture() {
        glBindTexture(GL_TEXTURE_2D, m_ColorTexture);
    }

    void FrameBuffer::Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
