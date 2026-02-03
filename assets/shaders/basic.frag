#version 330 core
out vec4 FragColor;

in float vLife;
in vec3 uvConverted;
in vec3 fragPos;


uniform vec3 lightPos;

void main()
{
   //vec3 lightPos = vec3(0.0f, 0.0f, 30.0f);
   vec3 recenteredPos = vec3((uvConverted.x * 2.0f)-1.0f, (uvConverted.y * 2.0f)-1.0f, 0.0f);
   float distQ = dot(recenteredPos.xy, recenteredPos.xy);

   if (distQ > 1.0)
      discard;

   float z = sqrt(1.0 - distQ);
   vec3 normal = vec3(recenteredPos.x, recenteredPos.y, z);
   vec3 lightDir = normalize(lightPos - fragPos);
   vec3 lightColor = vec3(1.0f, 56.0f/255.0f, 0.0f);
   float diffuseStrength = max(0.0f, dot(lightDir, normal));
   float brightnessMultiplier = 2.0f;
   float ambient = 0.1f;
   float totalBrightness = (diffuseStrength + ambient) * brightnessMultiplier;
   vec3 viewDir = vec3(0.0, 0.0, 1.0);
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
   vec3 finalLight = (lightColor * totalBrightness) + (vec3(0.5) * spec);
   float alpha = clamp(vLife, 0.0f, 1.0f);
   FragColor = vec4(finalLight, alpha);
}