#include "Game.h"
#include <iostream>
#include <GLFW\glfw3.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Mesh.h"
#include "Texture.h"
#include "Utilities.h"
#include <sstream>
#include "PerlinNoise.h"
#include <ctime>

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

	// TODO: DELETE THIS
	time_t timer;
	PerlinNoise pn(time(&timer));
#define DIM 512
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			vertexData.push_back(j);
			vertexData.push_back(i);
			double x = (double)j / ((double)DIM);
			double y = (double)i / ((double)DIM);
			double n = pn.noise(10 * x, 10 * y, 0.8);
			//n = n - floor(n);
			colorData.push_back((float)n);
		}
	}

	// Send data to OpenGL
	glGenVertexArrays(1, &vaoNoise);
	glGenBuffers(1, &vboVertices);
	glGenBuffers(1, &vboColor);

	glBindVertexArray(vaoNoise);

	glEnableVertexAttribArray(0);	// Vertex
	glEnableVertexAttribArray(1);	// Color

	// Vertices
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (char*)0);

	// Color
	glBindBuffer(GL_ARRAY_BUFFER, vboColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * colorData.size(), &colorData[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 1, GL_FLOAT, GL_FALSE, sizeof(float), (char*)0);

	// Cleanup
	glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
	glBindVertexArray(GL_NONE);

	// END TODO

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

	if (!noisemapShader.load("shaders/Perlin.vert", "shaders/Perlin.frag"))
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

	cameraTranslate = glm::translate(cameraTranslate, glm::vec3(0.f, 0.f, 5.f));
	cameraProjection = glm::perspective(45.f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 10000.f);
}

// Happens once per frame, used to update state of the game
void Game::update()
{
	// update timer so we have correct delta time since last update
	updateTimer->tick();

	float deltaTime = updateTimer->getElapsedTimeSeconds();

	if (InputManager::isKeyDownThisFrame(Keys::KEY_ESCAPE) || InputManager::isKeyDownThisFrame(Keys::KEY_Q))
	{
		exit(1);
	}

	float speed = 1.f;
	if (InputManager::isKeyDown(Keys::KEY_LEFT_SHIFT))
	{
		speed = 2.f;
	}

	glm::vec3 moveDirection;

	if (InputManager::isKeyDown(Keys::KEY_W))
	{
		moveDirection.z -= 1.f;
	}

	if (InputManager::isKeyDown(Keys::KEY_S))
	{
		moveDirection.z += 1.f;
	}

	if (InputManager::isKeyDown(Keys::KEY_A))
	{
		moveDirection.x -= 1.f;
	}

	if (InputManager::isKeyDown(Keys::KEY_D))
	{
		moveDirection.x += 1.f;
	}

	if (InputManager::isKeyDown(Keys::KEY_SPACE))
	{
		moveDirection.y += 1.f;
	}

	if (InputManager::isKeyDown(Keys::KEY_LEFT_CONTROL))
	{
		moveDirection.y -= 1.f;
	}

	if (glm::length(moveDirection) > 1.f)
	{
		moveDirection = glm::normalize(moveDirection);
	}

	cameraTranslate = glm::translate(cameraTranslate, moveDirection * speed * deltaTime);

	cameraTransform = glm::inverse(cameraTranslate * cameraRotate);
}

void Game::draw()
{
	glClearColor(0.f, 0.f, 1.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render stuff
	/*monkey1.draw(phong, cameraTransform, cameraProjection, pointLights);
	monkey2.draw(phong, cameraTransform, cameraProjection, pointLights);*/

	noisemapShader.bind();
	glBindVertexArray(vaoNoise);
	glDrawArrays(GL_POINTS, 0, colorData.size());
	glBindVertexArray(GL_NONE);
	noisemapShader.unbind();
}

void Game::mainLoop()
{
	update();
	draw();
}