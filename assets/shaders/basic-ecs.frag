#version 330 core

out vec4 outColor;

in vec4 ourColor;
in vec2 texCoord;

uniform sampler2D u_tex;

void main() 
{
	outColor = texture(u_tex, texCoord) * ourColor;
}