#version 330 core
layout(location = 0) in vec3 aPos;       
layout(location = 1) in vec3 aInstancePos; 

void main()
{
    gl_Position = vec4(aPos + aInstancePos, 1.0);
}