#version 330 core
out vec4 FragColor;
in float vLife;

void main()
{
   float alpha = clamp(vLife, 0.0f, 1.0f);
   FragColor = vec4(1.0f, 0.0f, 0.0f, alpha);
   // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);
   // FragColor = vec4(Color);
}
