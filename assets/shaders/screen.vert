#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 aTextureCoordinates;
out vec2 TextureCoordinates;

void main()
{
    TextureCoordinates = aTextureCoordinates;
    gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);
}
