#version 400

in vec3 fPos;			//position
in vec2 fuv;			//uv
in vec4 fColor;			//color
in vec4 fNormal;		//normal
out vec4 frag_colour;

uniform sampler2D texture;
uniform sampler2D texture2;

uniform vec3 CameraPos;
uniform vec3 SpecColor[8];			//spec colour
uniform vec3 SpecStrength = vec3(1,1,1);
uniform float SpecPow[8];

uniform int numLights;
uniform float lightAmbientStrength[8];
uniform vec3 lightPosition[8];
uniform vec3 lightColor[8];



void main ()
{
vec4 tempCol = vec4(0);
if(numLights <=8){

	for (int i = 0; i < numLights; i++){

		vec3 ambient = lightColor[i] * lightAmbientStrength[i];
		
		vec3 norm = normalize(fNormal.xyz);
		vec3 lightDir = normalize(fPos - lightPosition[i]);
	
		float diff  = max(dot(norm, lightDir) , 0.0f);
		vec3 diffuse = diff * lightColor[i];
	
		vec3 camToEye = normalize( CameraPos - fPos.xyz);
		vec3 reflection = reflect (lightDir, fNormal.xyz);
	
		float specTerm = max(0.0f, dot(reflection, camToEye)); 
		specTerm = pow(specTerm, SpecPow[i]);
		vec3 specular = SpecColor[i] * SpecStrength * specTerm; 
		tempCol = vec4 (ambient + lightColor[i] * diffuse + lightColor[i] * specular, 1.0) * texture2D(texture, fuv)* fColor;
		}
	}
		frag_colour = tempCol;
	
}

