#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in float tid;
layout(location = 3) in vec4 color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix = mat4(1.0f);
uniform mat4 modelMatrix = mat4(1.0f);

out DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} vs_out;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * position;
	vs_out.position = modelMatrix * position; // pos = postion 相对坐标（模型坐标系）， pos = modelMatrix * position 绝对坐标（世界坐标系）
	vs_out.uv = uv;
	vs_out.tid = tid;
	vs_out.color = color;
}