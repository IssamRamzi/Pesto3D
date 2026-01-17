#version 330 core
layout(location = 0) in vec3 aPos;       
layout(location = 1) in vec3 aInstancePos; 
layout(location = 2) in float lifeTime; 

uniform mat4 camMatrix;

struct Particle{
    vec3 position;
    vec3 velocity;
    vec3 size;
};

// https://stackoverflow.com/questions/4200224/random-noise-functions-for-glsl
float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

uniform float l;
out float lifetime;
//uniform float particleSize;

void main()
{
    lifetime = l;
    float r = rand(aInstancePos.xy);
    float g = rand(aInstancePos.yz + 10.0);
    float b = rand(aInstancePos.xz + 20.0);

    mat4 model = mat4(1.0);
    float particleSize = 0.1;
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