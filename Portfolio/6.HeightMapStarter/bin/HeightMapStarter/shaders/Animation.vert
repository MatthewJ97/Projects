#version 410
in vec4 position;
in vec4 normal;
in vec4 tangent;
in vec2 tex_coord;
in vec4 weights;
in vec4 indices;

out vec3 fPos;
out vec4 fNormal;
out vec2 fuv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform bool useBonesAndWeights;
uniform mat4 global;
// we need to give our bone array a limit
const int MAX_BONES = 128;
uniform mat4 bones[MAX_BONES];
void main()
{
fPos = position.xyz;
fNormal = normal;
fuv = tex_coord;
// cast the indices to integer's so they can index an array

ivec4 index = ivec4(indices);

// sample bones and blend up to 4
	if(weights != vec4(0,0,0,0)){

	vec4 P = bones[ index.x ] * position * weights.x;
	P += bones[ index.y ] * position * weights.y;
	P += bones[ index.z ] * position * weights.z;
	P += bones[ index.w ] * position * weights.w;
	gl_Position = projection * view * model * P;
	}
	else {
	vec4 P = bones[ index.x ] * position;
	P +=	 bones[ index.y ] * position;
	P +=	 bones[ index.z ] * position;
	P +=	 bones[ index.w ] * position;
	gl_Position = projection * view * model * P; 
	}
}
