#version 400

in vec4 vPosition;
in vec4 vNormal;
in vec2 vuv;
in vec4 vColor;

out vec3 fPos;
out vec2 fuv;
out vec4 fNormal;
out vec4 fColor;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main ()
{
	fPos = vPosition.xyz;
	fColor = vColor;
	fuv = vuv;
	fNormal = vNormal;	
	gl_Position = projection * view * model * vPosition;
}
