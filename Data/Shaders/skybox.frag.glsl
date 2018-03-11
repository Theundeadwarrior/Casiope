#version 450

in vec2 texCoord;

uniform sampler2D texture1;

out vec4 frag_colour;

void main()
{
	frag_colour = texture(texture1, texCoord);
}