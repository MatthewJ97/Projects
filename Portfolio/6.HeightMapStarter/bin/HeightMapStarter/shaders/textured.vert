#version 410
in vec4 position;
in vec4 normal;
in vec2 uv; 
out vec3 fPos;
out vec2 fuv;
out vec4 fNormal;
uniform mat4 projection; 
uniform mat4 view; 
uniform mat4 model; 

void main() {
fPos = position;
fNormal = normal;
fuv = uv; 
gl_Position = projection*view*model*position; 
};
