#version 420 core

layout (location=0) in vec3 inVert;
layout (location=1) in vec2 inUV;
layout (location=2) in vec3 inNormal;

out vec3 fragmentNormal;

struct Light
{
  vec3 position;
  vec4 diffuse;
};

uniform Light light;
uniform vec4 diffuseColour;

out vec3 lightIntensity;
uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 normalMatrix;

void main()
{
  fragmentNormal=normalize(normalMatrix*inNormal);
  vec4 eyeCords = MV * vec4(inVert,1);
  vec3 s = normalize(vec3(light.position-eyeCords.xyz));
  lightIntensity=light.diffuse.rgb*diffuseColour.rgb*max(dot(s,fragmentNormal),0.0);
  gl_Position=MVP*vec4(inVert,1.0);
}
