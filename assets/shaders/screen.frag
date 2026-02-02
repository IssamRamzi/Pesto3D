#version 330 core
out vec4 FragColor;
in vec2 TextureCoordinates;
uniform sampler2D screenTexture;

const float offset = 1.0f / 1.0f;

void main()
{
    /* COLO INVERSION
    FragColor = vec4(vec3(1.0 - texture(screenTexture, TextureCoordinates)), 1.0f);*/
    //FragColor = texture(screenTexture, TextureCoordinates);

    vec2 offsets[9] = vec2[](
        vec2(-offset, offset),
        vec2(0.0f, offset),
        vec2(offset, offset),
        vec2(-offset, 0.0f),
        vec2(0.0f, 0.0f),
        vec2(offset, 0.0f),
        vec2(-offset, -offset),
        vec2(0.0f, -offset),
        vec2(offset, -offset)
    );

    float kernel[9] = float[](
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16
    );

    vec3 sampleTex[9];
    for (int i = 0; i < 9; i++) {
        sampleTex[i] = vec3(texture(screenTexture, TextureCoordinates.st + offsets[i]));
    }
    vec3 col = vec3(0.0f);
    for (int i = 0; i < 9; i++) {
        col += sampleTex[i] * kernel[i];
    }

    FragColor = vec4(col, 1.0f);

}
