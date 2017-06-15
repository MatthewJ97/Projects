#version 400

in vec3 fPos;			//position
in vec2 fuv;			//uv
in vec4 fColor;			//color
in vec3 fNormal;		//normal
out vec4 frag_colour;

uniform sampler2D texture;
uniform sampler2D texture2;

uniform vec3 CameraPos;
uniform vec3 SpecColor;			//spec colour
uniform vec3 SpecStrength = vec3(1,1,1);
uniform float SpecPow;

uniform float lightAmbientStrength;
uniform vec3 lightPosition;
uniform vec3 lightColor;
void main ()
{
	vec3 ambient = lightColor * lightAmbientStrength;
	
	vec3 norm = normalize(fNormal.xyz);
	vec3 lightDir = normalize(fPos - lightPosition);

	float diff  = max(dot(norm, lightDir) , 0.0f);
	vec3 diffuse = diff * lightColor;

	vec3 camToEye = normalize( CameraPos - fPos.xyz);
	vec3 reflection = reflect (lightDir, fNormal.xyz);

	float specTerm = max(0.0f, dot(reflection, camToEye)); 
	specTerm = pow(specTerm, SpecPow);
	vec3 specular = SpecColor * SpecStrength * specTerm; 
	frag_colour = vec4 (ambient + lightColor * diffuse + lightColor * specular, 1.0) * texture2D(texture, fuv)* fColor;
	
}

