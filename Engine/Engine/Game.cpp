#include "Game.h"
#include <iostream>
#include <GL\glut.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Mesh.h"
#include "Texture.h"
#include "Utilities.h"
#include <sstream>

Game::Game()
{
	
}

Game::~Game()
{
	passThrough.unload();
	phongNoTexture.unload();
	phong.unload();
}

// Happens once at the beginning of the game
void Game::initializeGame()
{
	updateTimer = std::make_shared<Timer>();

	glEnable(GL_DEPTH_TEST);

	Light light1;

	light1.position = glm::vec4(4.f, 4.f, 4.f, 1.f);
	light1.originalPosition = glm::vec4(4.f, 4.f, 4.f, 1.f);
	light1.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	light1.diffuse = glm::vec3(0.7f, 0.7f, 0.7f);
	light1.specular = glm::vec3(1.f, 1.f, 1.f);
	light1.specularExponent = 50.f;
	light1.constantAttenuation = 1.f;
	light1.linearAttenuation = 0.1f;
	light1.quadraticAttenuation = 0.01f;

	pointLights.push_back(light1);

	if (!passThrough.load("shaders/passthrough.vert", "shaders/passthrough.frag"))
	{
		std::cout << "Shaders failed to initialize." << std::endl;
		system("pause");
		exit(0);
	}

	if (!phongNoTexture.load("shaders/Phong.vert", "shaders/PhongNoTexture.frag"))
	{
		std::cout << "Shaders failed to initialize." << std::endl;
		system("pause");
		exit(0);
	}

	if (!phong.load("shaders/Phong.vert", "shaders/Phong.frag"))
	{
		std::cout << "Shaders failed to initialize." << std::endl;
		system("pause");
		exit(0);
	}

	if (!uvMap.load("shaders/UVMap.vert", "shaders/UVMap.frag"))
	{
		std::cout << "Shaders failed to initialize." << std::endl;
		system("pause");
		exit(0);
	}

	// Initialize monkey
	monkey1.loadMesh("meshes/Monkey.obj");
	monkey1.loadTexture(TextureType::Diffuse, "textures/fur.png");
	monkey1.loadTexture(TextureType::Specular, "textures/specular.png");
	//monkey1.color = glm::vec4(1.f, 0.f, 0.f, 1.f);
	monkey2.loadMesh("meshes/Monkey.obj");
	monkey2.loadTexture(TextureType::Diffuse, "textures/fur.png");
	monkey2.loadTexture(TextureType::Specular, "textures/specular.png");
	//monkey2.color = glm::vec4(0.f, 1.f, 0.f, 1.f);

	monkey2.transform = glm::translate(monkey2.transform, glm::vec3(2.f, 0.f, 0.f));

	cameraTransform = glm::translate(cameraTransform, glm::vec3(0.f, 0.f, -5.f));
	cameraProjection = glm::perspective(45.f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 10000.f);
}

// Happens once per frame, used to update state of the game
void Game::update()
{
	// update timer so we have correct delta time since last update
	updateTimer->tick();

	float deltaTime = updateTimer->getElapsedTimeSeconds();

	if (InputManager::isKeyDownThisFrame(Keys::Esc) || InputManager::isKeyDownThisFrame(Keys::Q))
	{
		exit(1);
	}

	/*if (InputManager::isKeyDownThisFrame(Keys::R))
	{
		shouldRotate = !shouldRotate;
	}*/
	shouldRotate = InputManager::isKeyDown(Keys::R);

	float speed = 1.f;
	if (InputManager::isModifierDown(Modifiers::Shift))
	{
		speed = 2.f;
	}

	if (shouldRotate)
	{
		monkey1.rotate = glm::rotate(monkey1.rotate, speed * deltaTime * (glm::pi<float>() / 4.f), glm::vec3(0.f, 1.f, 0.f));
	}

	if (InputManager::isKeyDown(Keys::W))
	{
		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(0.f, deltaTime * 1.f, 0.f));
	}

	if (InputManager::isKeyDown(Keys::A))
	{
		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(-deltaTime * 1.f, 0.f, 0.f));
	}

	if (InputManager::isKeyDown(Keys::S))
	{
		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(0.f, -deltaTime * 1.f, 0.f));
	}

	if (InputManager::isKeyDown(Keys::D))
	{
		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(deltaTime * 1.f, 0.f, 0.f));
	}

	if (InputManager::isKeyDown(Keys::Z))
	{
		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(0.f, 0.f, deltaTime * 1.f));
	}

	if (InputManager::isKeyDown(Keys::X))
	{
		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(0.f, 0.f, -deltaTime * 1.f));
	}

	if (InputManager::isKeyDown(Keys::P))
	{
		monkey1.scale += deltaTime * 1.f;
	}

	if (InputManager::isKeyDown(Keys::O))
	{
		monkey1.scale -= deltaTime * 1.f;
	}

	monkey1.transform = monkey1.translate * monkey1.rotate * glm::scale(glm::mat4(), glm::vec3(monkey1.scale));
}

void Game::draw()
{
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render stuff
	monkey1.draw(phong, cameraTransform, cameraProjection, pointLights);
	monkey2.draw(phong, cameraTransform, cameraProjection, pointLights);

	glutSwapBuffers();
}