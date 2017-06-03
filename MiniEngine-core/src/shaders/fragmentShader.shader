#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 lightPosition;

in vec4 pos;

void main()
{
//	color = vec4(1.0f, 0.0f, 0.0f, 1.0f); //for text
	float intensity = 1.0 / length(pos.xy - lightPosition);
	color = colour * intensity;
}