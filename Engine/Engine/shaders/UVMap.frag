#version 420

in vec3 position;
in vec2 texCoord;
in vec3 normal;

out vec4 outColor;

void main()
{
	outColor.r = texCoord.x;
	outColor.g = texCoord.y;
	outColor.b = 0;
	outColor.a = 1;
}