precision highp float;

uniform highp vec4 colour;
uniform highp vec2 lightPosition;

varying	highp vec2 vs_uv;
varying	highp vec4 vs_position;
varying	highp float vs_tid;
varying	highp vec4 vs_color;

uniform sampler2D u_texture;

void main()
{
	float intensity = 1.0 / length(vs_position.xy - lightPosition);
	vec4 texColor = vs_color;
	texColor = vs_color * texture2D(u_texture, vs_uv);
	gl_FragColor = texColor * intensity;
}