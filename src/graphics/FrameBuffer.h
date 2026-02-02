//
// Created by Issam on 26/01/2026.
//

#ifndef PESTO3D_FRAMEBUFFER_H
#define PESTO3D_FRAMEBUFFER_H
#include "iBuffer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
namespace Pesto {
    class FrameBuffer : iBuffer {
    public:
        FrameBuffer(f32 width, f32 height);
        void Bind();
        void Unbind();
        void BindTexture();

    private:
        GLuint m_ColorTexture, m_RBO;
    };


}


#endif //PESTO3D_FRAMEBUFFER_H