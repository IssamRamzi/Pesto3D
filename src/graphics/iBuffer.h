//
// Created by Issam on 30/12/2025.
//

#ifndef PESTO3D_IBUFFERE_H
#define PESTO3D_IBUFFERE_H
#include "../globals.h"

namespace Pesto {
    class iBuffer {
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
    protected:
        u32 m_bufferID;
    };
}
#endif //PESTO3D_IBUFFERE_H