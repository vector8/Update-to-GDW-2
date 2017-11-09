#pragma once
#include <glm\glm.hpp>
#include <vector>
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Light.h"
#include "Material.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	Mesh mesh;
	Material mat;

	glm::mat4 transform;
	glm::mat4 translate;
	glm::mat4 rotate;
	float scale = 1;

	void loadMesh(std::string meshFile);
	void loadTexture(TextureType type, std::string texFile);

	void draw(ShaderProgram &shader, glm::mat4 &cameraTransform,
		glm::mat4 &cameraProjection, std::vector<Light> &pointLights, Light &directionalLight);
};