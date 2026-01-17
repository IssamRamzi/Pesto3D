//
// Created by Issam on 17/01/2026.
//

#include "CubeMap.h"
#include "stb/stb_image.h"

void Pesto::CubeMap::Init() {

    facesCubemap.emplace_back("../assets/textures/cubemap/left.jpg");
    facesCubemap.emplace_back("../assets/textures/cubemap/right.jpg");
    facesCubemap.emplace_back("../assets/textures/cubemap/top.jpg");
    facesCubemap.emplace_back("../assets/textures/cubemap/bottom.jpg");
    facesCubemap.emplace_back("../assets/textures/cubemap/front.jpg");
    facesCubemap.emplace_back("../assets/textures/cubemap/back.jpg");

    VAO.Bind();
    VBO.SetData(skyboxVertices, 3, sizeof(skyboxVertices) / sizeof(f32));
    EBO.Bind();
    VAO.AddBuffer(VBO, 0, 3, sizeof(f32) * 3, (void*)0);
    VBO.Unbind();
    EBO.Unbind();
    VAO.Unbind();

    glGenTextures(1, &cubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // These are very important to prevent seams
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++)
    {
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(false);

        unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D
            (
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                width,
                height,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
            stbi_image_free(data);
        }
    }
}

void Pesto::CubeMap::Draw(Shader &shader, const GeoMa::Matrix4F& view, const GeoMa::Matrix4F& proj) {
    glDepthFunc(GL_LEQUAL);
    shader.EnableShader();
    shader.SetUniformMat4("view", view);
    shader.SetUniformMat4("projection", proj);
    VAO.Bind();
    EBO.Bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    VAO.Unbind();
    EBO.Unbind();
    shader.DisableShader();
}
