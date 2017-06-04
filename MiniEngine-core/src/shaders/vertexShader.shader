#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix = mat4(1.0f);
uniform mat4 modelMatrix = mat4(1.0f);

out DATA
{
	vec4 position;
	vec4 color;
} vs_out;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix *  position;
	vs_out.position = modelMatrix * position; // pos = postion ������꣨ģ������ϵ���� pos = modelMatrix * position �������꣨��������ϵ��
	vs_out.color = color;
}