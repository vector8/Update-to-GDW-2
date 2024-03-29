#version 420

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

layout(location = 0) in vec3 in_vert;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal;

out vec3 position;
out vec2 texCoord;
out vec3 normal;

void main()
{
	texCoord = in_uv;
	normal = mat3(uView) * mat3(uModel) * in_normal;

	vec4 viewSpacePos = uView * uModel * vec4(in_vert, 1.0f);
	position = viewSpacePos.xyz;

	gl_Position = vec4((in_uv.x * 2.0f) - 1, (in_uv.y * 2.0f) - 1, 0, 1);
}