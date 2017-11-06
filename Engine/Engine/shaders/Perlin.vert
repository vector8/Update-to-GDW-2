#version 420

layout(location = 0) in vec2 in_vert;
layout(location = 1) in float in_col;

out float color;

void main()
{
	color = in_col;
	vec2 pos = vec2(in_vert.x / 512, in_vert.y / 512);
	pos = pos * 2 - 1;
	gl_Position = vec4(pos, 0, 1);
}