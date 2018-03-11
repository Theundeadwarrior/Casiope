#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCell;

out vec2 texCoord;

void main(void)
{	
    gl_Position = projection * view * model * vec4(position, 1.0);
	texCoord = vec2(textureCell.x / 6.0, textureCell.y);
}