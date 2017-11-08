#pragma once
#include <vector>

class PerlinNoise
{
public:
	// Initialize with the reference values for the permutation vector
	PerlinNoise();
	// Generate a new permutation vector based on the value of seed
	PerlinNoise(unsigned int seed);
	~PerlinNoise();

	// Get a noise value. For 2D images, z can have any value
	double noise(double x, double y, double z);

private:
	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);

	// The permutation vector
	std::vector<int> p;
};

#pragma region TEST_CODE
// IN INITIALIZE
//time_t timer;
//PerlinNoise pn(time(&timer));
//#define DIM 512
//for (int i = 0; i < DIM; i++)
//{
//	for (int j = 0; j < DIM; j++)
//	{
//		vertexData.push_back(j);
//		vertexData.push_back(i);
//		double x = (double)j / ((double)DIM);
//		double y = (double)i / ((double)DIM);
//		double n = pn.noise(10 * x, 10 * y, 0.8);
//		//n = n - floor(n);
//		colorData.push_back((float)n);
//	}
//}
//
//// Send data to OpenGL
//glGenVertexArrays(1, &vaoNoise);
//glGenBuffers(1, &vboVertices);
//glGenBuffers(1, &vboColor);
//
//glBindVertexArray(vaoNoise);
//
//glEnableVertexAttribArray(0);	// Vertex
//glEnableVertexAttribArray(1);	// Color
//
//								// Vertices
//glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
//glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (char*)0);
//
//// Color
//glBindBuffer(GL_ARRAY_BUFFER, vboColor);
//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * colorData.size(), &colorData[0], GL_STATIC_DRAW);
//glVertexAttribPointer((GLuint)1, 1, GL_FLOAT, GL_FALSE, sizeof(float), (char*)0);
//
//// Cleanup
//glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
//glBindVertexArray(GL_NONE);

// IN DRAW
//noisemapShader.bind();
//glBindVertexArray(vaoNoise);
//glDrawArrays(GL_POINTS, 0, colorData.size());
//glBindVertexArray(GL_NONE);
//noisemapShader.unbind();
#pragma endregion
