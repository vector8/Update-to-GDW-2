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
	mat.loadTexture(type, texFile);
}

void GameObject::draw(ShaderProgram &shader, glm::mat4 &cameraTransform,
	glm::mat4 &cameraProjection, std::vector<Light> &pointLights, Light &directionalLight)
{
	shader.bind();
	shader.sendUniformMat4("uModel", glm::value_ptr(transform), false);
	shader.sendUniformMat4("uView", glm::value_ptr(cameraTransform), false);
	shader.sendUniformMat4("uProj", glm::value_ptr(cameraProjection), false);

	// Texture
	shader.sendUniform("material.diffuse", 0);
	shader.sendUniform("material.specular", 1);
	shader.sendUniform("material.hue", mat.hue);
	shader.sendUniform("material.specularExponent", mat.specularExponent);

	for (int i = 0; i < pointLights.size(); i++)
	{
		std::string prefix = "pointLights[" + std::to_string(i) + "].";
		shader.sendUniform(prefix + "position", cameraTransform * pointLights[i].positionOrDirection);
		shader.sendUniform(prefix + "ambient", pointLights[i].ambient);
		shader.sendUniform(prefix + "diffuse", pointLights[i].diffuse);
		shader.sendUniform(prefix + "specular", pointLights[i].specular);
		shader.sendUniform(prefix + "specularExponent", pointLights[i].specularExponent);
		shader.sendUniform(prefix + "constantAttenuation", pointLights[i].constantAttenuation);
		shader.sendUniform(prefix + "linearAttenuation", pointLights[i].linearAttenuation);
		shader.sendUniform(prefix + "quadraticAttenuation", pointLights[i].quadraticAttenuation);
	}

	shader.sendUniform("directionalLight.direction", cameraTransform * directionalLight.positionOrDirection);
	shader.sendUniform("directionalLight.ambient", directionalLight.ambient);
	shader.sendUniform("directionalLight.diffuse", directionalLight.diffuse);
	shader.sendUniform("directionalLight.specular", directionalLight.specular);

	glActiveTexture(GL_TEXTURE0);
	mat.diffuse.bind();

	glActiveTexture(GL_TEXTURE1);
	mat.specular.bind();

	glBindVertexArray(mesh.vao);
	glDrawArrays(GL_TRIANGLES, 0, mesh.getNumVertices());
	glBindVertexArray(GL_NONE);

	mat.specular.unbind();
	glActiveTexture(GL_TEXTURE0);
	mat.diffuse.unbind();

	shader.unbind();
}