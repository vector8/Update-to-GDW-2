#pragma once
#include <string>
#include <GL\glew.h>

class Mesh
{
public:
	Mesh();
	~Mesh();

	// Load a mesh and send it to OpenGL
	bool loadFromFile(const std::string &file);

	// Release data from OpenGL (VRAM)
	void unload();

	unsigned int getNumFaces() const;
	unsigned int getNumVertices() const;

	// OpenGL buffers and objects
	GLuint vboVertices = 0;
	GLuint vboUVs = 0;
	GLuint vboNormals = 0;
	GLuint vao = 0;

private:
	unsigned int numFaces = 0;
	unsigned int numVertices = 0;
};