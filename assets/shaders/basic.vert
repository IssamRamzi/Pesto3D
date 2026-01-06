#version 330 core
layout(location = 0) in vec3 aPos;       
layout(location = 1) in vec3 aInstancePos; 

uniform mat4 camMatrix;

void main()
{
    gl_Position = camMatrix * vec4(aPos + aInstancePos, 1.0);
}