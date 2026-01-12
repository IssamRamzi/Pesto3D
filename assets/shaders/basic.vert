#version 330 core
layout(location = 0) in vec3 aPos;       
layout(location = 1) in vec3 aInstancePos; 

uniform mat4 camMatrix;
uniform float particleSize = 0.1;

struct Particle{
    vec3 position;
    vec3 velocity;
    vec3 size;
};

// https://stackoverflow.com/questions/4200224/random-noise-functions-for-glsl
float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

out vec3 vColor;

void main()
{
    float r = rand(aInstancePos.xy);
    float g = rand(aInstancePos.yz + 10.0);
    float b = rand(aInstancePos.xz + 20.0);
    vColor = vec3(r, g, b);


    mat4 model = mat4(1.0);

    // scale
    model[0][0] = particleSize;
    model[1][1] = particleSize;
    model[2][2] = particleSize;

    // transla
    model[3][0] = aInstancePos.x;
    model[3][1] = aInstancePos.y;
    model[3][2] = aInstancePos.z;
    gl_Position = camMatrix * model * vec4(aPos, 1.0);
}