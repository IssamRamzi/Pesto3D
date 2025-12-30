#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform vec3 offsets[100];

void main()
{
    vec3 offset = offsets[gl_InstanceID];
    gl_Position = vec4(aPos + offset, 1.0);
}