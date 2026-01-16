#version 330 core
out vec4 FragColor;
in float lifetime;
void main()
{
   FragColor = vec4(1.0f, 0.5f, 0.2f, lifetime);
   // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);
   // FragColor = vec4(Color);
}
