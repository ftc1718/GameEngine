#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 lightPosition;

in DATA
{
	vec4 position;
	vec4 color;
} fs_in;

void main()
{
	float intensity = 1.0f / length(fs_in.position.xy - lightPosition);
	color = fs_in.color * intensity;
}