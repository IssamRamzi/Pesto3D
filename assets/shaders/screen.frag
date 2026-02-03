#version 330 core
out vec4 FragColor;

in vec2 TextureCoordinates;
uniform sampler2D screenTexture;

uniform bool hdrEnabled;
uniform float exposure;
uniform float gamma;

const float offset = 1.0 / 300.0;

void main()
{
    vec3 originalColor = texture(screenTexture, TextureCoordinates).rgb;

    vec2 offsets[9] = vec2[](
    vec2(-offset, offset),  vec2(0.0f, offset),  vec2(offset, offset),
    vec2(-offset, 0.0f),    vec2(0.0f, 0.0f),    vec2(offset, 0.0f),
    vec2(-offset, -offset), vec2(0.0f, -offset), vec2(offset, -offset)
    );

    float kernel[9] = float[](
    1.0 / 16, 2.0 / 16, 1.0 / 16,
    2.0 / 16, 4.0 / 16, 2.0 / 16,
    1.0 / 16, 2.0 / 16, 1.0 / 16
    );

    vec3 blurredColor = vec3(0.0f);
    for (int i = 0; i < 9; i++) {
        blurredColor += vec3(texture(screenTexture, TextureCoordinates.st + offsets[i])) * kernel[i];
    }

    vec3 result = originalColor + blurredColor;

    if (hdrEnabled) {
        result = vec3(1.0) - exp(-result * exposure);
        result = pow(result, vec3(1.0 / gamma));
    }

    FragColor = vec4(result, 1.0f);
}