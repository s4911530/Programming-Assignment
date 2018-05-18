#version 420 core

layout (location=0) out vec4 fragColour;

struct Light
{
  vec3 position;
  vec4 diffuse;
};

uniform Light light;
uniform vec4 diffuseColour;
in vec3 lightIntensity;


in vec3 fragmentNormal;

void main()
{
  fragColour.rgb= lightIntensity;
}
