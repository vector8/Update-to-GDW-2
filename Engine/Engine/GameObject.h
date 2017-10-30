#pragma once
#include <glm\glm.hpp>
#include <vector>
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Light.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	Mesh mesh;
	Texture diffuse;
	Texture specular;
	Texture normal;
	glm::mat4 transform;
	glm::vec3 color = glm::vec3(1.f, 1.f, 1.f);

	glm::mat4 translate;
	glm::mat4 rotate;
	float scale = 1;

	void loadMesh(std::string meshFile);
	void loadTexture(TextureType type, std::string texFile);

	void draw(ShaderProgram &shader, glm::mat4 &cameraTransform, 
		glm::mat4 &cameraProjection, std::vector<Light> &pointLights);
};