#version 410
in vec4 vNormal;
in vec2 vuv;


out vec4 FragColor;

uniform sampler2D diffuseTexture;

uniform vec3 CameraPos;
uniform vec3 SpecColor[8];			//spec colour
uniform vec3 SpecStrength = vec3(1,1,1);
uniform float SpecPow[8];

uniform int numLights;
uniform float lightAmbientStrength[8];
uniform vec3 lightPosition[8];
uniform vec3 lightColor[8];

void main() 
{

	FragColor = texture2D(diffuseTexture, vuv)  * vec4(1,1,1,1);
}
