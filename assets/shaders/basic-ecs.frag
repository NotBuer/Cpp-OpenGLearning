#version 330 core

out vec4 outColor;

in vec4 ourColor;
in vec2 texCoord;

uniform sampler2D u_tex;
uniform sampler2D u_tex2;

void main() 
{
	//outColor = mix(texture(u_tex, texCoord), texture(u_tex2, texCoord), 0.3);
	outColor = ourColor;
}