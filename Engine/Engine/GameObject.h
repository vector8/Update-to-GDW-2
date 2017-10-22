#pragma once
#include <glm\glm.hpp>
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	Mesh mesh;
	Texture texture;
	glm::mat4 transform;
	glm::vec4 color;

	glm::mat4 translate;
	glm::mat4 rotate;
	float scale = 1;

	void loadMesh(std::string meshFile);
	void loadTexture(std::string texFile);

	void draw(ShaderProgram &shader, glm::mat4 &cameraTransform, 
		glm::mat4 &cameraProjection);
};