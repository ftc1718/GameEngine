attribute vec4 position;
attribute vec2 uv;
attribute float tid;
attribute vec4 color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;


varying	highp vec2 vs_uv;
varying	highp vec4 vs_position;
varying	highp float vs_tid;
varying	highp vec4 vs_color;

void main()
{
	gl_Position = projectionMatrix * position;
	vs_position = position;
	vs_uv = uv;
	vs_tid = tid;
	vs_color = color;
}