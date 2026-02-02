#version 330 core
out vec4 FragColor;

in vec3 texCoords;

uniform samplerCube skybox;

void main()
{
    vec4 color = texture(skybox, texCoords);
    FragColor = vec4(color.rgb, color.a * 0.3);
}