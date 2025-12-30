//
// Created by Issam on 30/12/2025.
//

#ifndef PESTO3D_VERTEXARRAYS_H
#define PESTO3D_VERTEXARRAYS_H
#include "iBuffer.h"


namespace Pesto{
    class VertexBuffer;

    class VertexArrays : iBuffer {
    public:
        VertexArrays();
        ~VertexArrays();

        void Bind() override;
        void Unbind() override;

        void AddBuffer(VertexBuffer& vbo, unsigned int index, unsigned int componentsCount, int stride, void *offset);
    };
}

#endif //PESTO3D_VERTEXARRAYS_H