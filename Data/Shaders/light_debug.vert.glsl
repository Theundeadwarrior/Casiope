#version 450


in vec4 position;

uniform mat4 view;
uniform mat4 projection;

void main () {
	gl_Position = projection * view * position;
}
