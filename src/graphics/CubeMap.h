//
// Created by Issam on 17/01/2026.
//
// https://github.com/VictorGordan/opengl-tutorials/blob/main/YoutubeOpenGL%2019%20-%20Cubemaps%20%26%20Skyboxes/Main.cpp


#ifndef PESTO3D_CUBEMAP_H
#define PESTO3D_CUBEMAP_H
#include <vector>

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArrays.h"
#include "VertexBuffer.h"
#include "../globals.h"
#include "../core/Camera.h"

namespace Pesto{
class CubeMap {
public:
    CubeMap() = default;


    void Init();

    void Draw(Shader& shader, const GeoMa::Matrix4F& view, const GeoMa::Matrix4F& proj);


private:
    inline static f32 skyboxVertices[] = {
        //   Coordinates
        -1.0f, -1.0f,  1.0f,//        7--------6
         1.0f, -1.0f,  1.0f,//       /|       /|
         1.0f, -1.0f, -1.0f,//      4--------5 |
        -1.0f, -1.0f, -1.0f,//      | |      | |
        -1.0f,  1.0f,  1.0f,//      | 3------|-2
         1.0f,  1.0f,  1.0f,//      |/       |/
         1.0f,  1.0f, -1.0f,//      0--------1
        -1.0f,  1.0f, -1.0f
    };

    inline static u32 skyboxIndices[] =
    {
        // Right
        1, 2, 6,
        6, 5, 1,
        // Left
        0, 4, 7,
        7, 3, 0,
        // Top
        4, 5, 6,
        6, 7, 4,
        // Bottom
        0, 3, 2,
        2, 1, 0,
        // Back
        0, 1, 5,
        5, 4, 0,
        // Front
        3, 7, 6,
        6, 2, 3
    };


    Pesto::VertexArrays VAO;
    Pesto::VertexBuffer VBO;
    Pesto::IndexBuffer EBO{skyboxIndices, 36};
    std::vector<std::string> facesCubemap;
    GLuint cubemapTexture;




};
}

#endif //PESTO3D_CUBEMAP_H