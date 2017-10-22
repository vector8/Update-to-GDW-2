#pragma once
#include <SFML\OpenGL.hpp>

namespace flopse
{
	// Mesh Constants
	GLfloat rubiksCube[] =
	{
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,	// 0
		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,	// 1
		0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,	// 2
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,	// 0
		0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,	// 2
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,	// 3
		-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,	// 1
		0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,	// 2
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,		// 6
		-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,	// 1
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,	// 5
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,		// 6
		0.5f, -0.5f, 0.5f, 1.0f, 0.5f, 0.0f,	// 2
		0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.0f,	// 3
		0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.0f,	// 7
		0.5f, -0.5f, 0.5f, 1.0f, 0.5f, 0.0f,	// 2
		0.5f, 0.5f, 0.5f, 1.0f, 0.5f, 0.0f,		// 6
		0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.0f,	// 7
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,	// 0
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,	// 3
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,	// 7
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,	// 0
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,	// 4
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,	// 7
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,	// 0
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,	// 1
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,	// 5
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,	// 0
		-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,	// 4
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,	// 5
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,	// 4
		-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,	// 5
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,		// 6
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,	// 4
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,		// 6
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f		// 7
	};

	GLfloat vertices3[] = {
		// vertex					uv			normal
		-30.f, 0.f, -30.f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		30.f, 0.f, -30.f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		30.f, 60.f, -30.f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		30.f, 60.f, -30.f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		-30.f, 60.f, -30.f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		-30.f, 0.f, -30.f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

		-30.f, 0.f, 30.f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		30.f, 0.f, 30.f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		30.f, 60.f, 30.f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		30.f, 60.f, 30.f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-30.f, 60.f, 30.f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-30.f, 0.f, 30.f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		-30.f, 60.f, 30.f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-30.f, 60.f, -30.f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-30.f, 0.f, -30.f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-30.f, 0.f, -30.f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-30.f, 0.f, 30.f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-30.f, 60.f, 30.f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,

		30.f, 60.f, 30.f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		30.f, 60.f, -30.f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		30.f, 0.f, -30.f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		30.f, 0.f, -30.f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		30.f, 0.f, 30.f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		30.f, 60.f, 30.f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-30.f, 0.f, -30.f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		30.f, 0.f, -30.f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		30.f, 0.f, 30.f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		30.f, 0.f, 30.f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		-30.f, 0.f, 30.f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		-30.f, 0.f, -30.f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,

		-30.f, 60.f, -30.f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		30.f, 60.f, -30.f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		30.f, 60.f, 30.f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		30.f, 60.f, 30.f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-30.f, 60.f, 30.f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-30.f, 60.f, -30.f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f
	};

	GLfloat vertices2[] =
	{
		-0.5f, -0.5f, 0.0f, 1.0f, 0.73f, 0.0f,
		0.0f, -0.5f, 0.0f, 1.0f, 0.65f, 0.0f,
		-0.25f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.25f, 0.0f, 0.0f, 1.0f, 0.73f, 0.0f,
		0.25f, 0.0f, 0.0f, 1.0f, 0.65f, 0.0f,
		0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 1.0f, 0.73f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.65f, 0.0f,
		0.25f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f
	};

	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		1, 2, 6,
		1, 5, 6,
		2, 3, 7,
		2, 6, 7,
		0, 3, 7,
		0, 4, 7,
		0, 1, 5,
		0, 4, 5,
		4, 5, 6,
		4, 6, 7
	};
}