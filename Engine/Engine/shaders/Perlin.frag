#version 420

in float color;

out vec4 outColor;

void main()
{
	outColor = vec4(color, color, color, 1);
}