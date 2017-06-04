#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix = mat4(1.0f); 
uniform mat4 modelMatrix = mat4(1.0f);

out vec4 pos;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix *  position;
	pos = modelMatrix * position; // pos = postion 相对坐标（模型坐标系）， pos = modelMatrix * position 绝对坐标（世界坐标系）
}