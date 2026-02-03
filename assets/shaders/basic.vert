#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aInstancePos;
layout(location = 2) in float aparticleSize;
layout(location = 3) in float aLifetime;

uniform mat4 camMatrix;

struct Particle
{
    vec3 position;
    vec3 velocity;
    vec3 size;
};

// https://stackoverflow.com/questions/4200224/random-noise-functions-for-glsl
float rand(vec2 co)
{
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

//uniform float l;
//uniform float particleSize;

out float vLife;
out vec3 uvConverted;
out vec3 fragPos;

vec3 convertUv(vec3 positions)
{
    vec3 newPos = vec3(positions.x + 0.5f, positions.y + 0.5f, 0.0f);
    return newPos;
}

void main()
{
    //lifetime = l;
    vLife = aLifetime;
    uvConverted = convertUv(aPos);
    float r = rand(aInstancePos.xy);
    float g = rand(aInstancePos.yz + 10.0);
    float b = rand(aInstancePos.xz + 20.0);

    mat4 model = mat4(1.0);

    // scale
    model[0][0] = aparticleSize;
    model[1][1] = aparticleSize;
    model[2][2] = aparticleSize;

    // transla
    model[3][0] = aInstancePos.x;
    model[3][1] = aInstancePos.y;
    model[3][2] = aInstancePos.z;
    vec4 worldPos = model * vec4(aPos, 1.0f);
    fragPos = vec3(worldPos);

    gl_Position = camMatrix * model * vec4(aPos, 1.0);
}