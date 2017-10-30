#include "GameObject.h"
#include <glm\gtc\type_ptr.hpp>
#include <iostream>

GameObject::GameObject()
{
	
}

GameObject::~GameObject()
{
	mesh.unload();
}

void GameObject::loadMesh(std::string meshFile)
{
	if (!mesh.loadFromFile(meshFile))
	{
		std::cout << "Model failed to load." << std::endl;
		system("pause");
		exit(0);
	}
}

void GameObject::loadTexture(TextureType type, std::string texFile)
{
	switch (type)
	{
	case Diffuse:
		if (!diffuse.load(texFile))
		{
			system("pause");
			exit(0);
		}
		break;
	case Specular:
		if (!specular.load(texFile))
		{
			system("pause");
			exit(0);
		}
		break;
	case Normal:
		if (!normal.load(texFile))
		{
			system("pause");
			exit(0);
		}
		break;
	default:
		{
			std::cout << "Error - TextureType not found: " << type << std::endl;
			system("pause");
			exit(0);
		}
		break;
	}
	
}

void GameObject::draw(ShaderProgram &shader, glm::mat4 &cameraTransform,
	glm::mat4 &cameraProjection, std::vector<Light> &pointLights)
{
	shader.bind();
	shader.sendUniformMat4("uModel", glm::value_ptr(transform), false);
	shader.sendUniformMat4("uView", glm::value_ptr(cameraTransform), false);
	shader.sendUniformMat4("uProj", glm::value_ptr(cameraProjection), false);

	// Texture
	shader.sendUniform("material.diffuse", 0);
	shader.sendUniform("material.specular", 1);
	shader.sendUniform("material.hue", color);
	shader.sendUniform("material.specularExponent", 50.f);

	for (int i = 0; i < pointLights.size(); i++)
	{
		std::string prefix = "pointLights[" + std::to_string(i) + "].";
		shader.sendUniform(prefix + "position", cameraTransform * pointLights[i].position);
		shader.sendUniform(prefix + "ambient", pointLights[i].ambient);
		shader.sendUniform(prefix + "diffuse", pointLights[i].diffuse);
		shader.sendUniform(prefix + "specular", pointLights[i].specular);
		shader.sendUniform(prefix + "constantAttenuation", pointLights[i].constantAttenuation);
		shader.sendUniform(prefix + "linearAttenuation", pointLights[i].linearAttenuation);
		shader.sendUniform(prefix + "quadraticAttenuation", pointLights[i].quadraticAttenuation);
	}


	glActiveTexture(GL_TEXTURE0);
	diffuse.bind();

	glActiveTexture(GL_TEXTURE1);
	specular.bind();

	glBindVertexArray(mesh.vao);
	glDrawArrays(GL_TRIANGLES, 0, mesh.getNumVertices());
	glBindVertexArray(GL_NONE);

	specular.unbind();
	glActiveTexture(GL_TEXTURE0);
	diffuse.unbind();

	shader.unbind();
}