#version 450


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 inTexCoord;

out VertexShaderOutput {
	vec3 positionVS;
	vec2 texCoord;
	vec3 normalVS;
} vertex_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main () {
	gl_Position = projection * view * model *  vec4(position, 1.0);
	vertex_out.texCoord = inTexCoord;
	vertex_out.positionVS = (view * model * vec4(position, 1.0)).xyz;
	vertex_out.normalVS = mat3(view) * normal;
}
