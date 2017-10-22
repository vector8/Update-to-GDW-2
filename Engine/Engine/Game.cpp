#include "Game.h"
#include <iostream>
#include <GL\glut.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Mesh.h"
#include "Texture.h"

Game::Game()
{
}

Game::~Game()
{
	delete updateTimer;

	passThrough.unload();
	phongNoTexture.unload();
}

// Happens once at the beginning of the game
void Game::initializeGame()
{
	updateTimer = new Timer();

	glEnable(GL_DEPTH_TEST);

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

	// Initialize monkey
	monkey1.loadMesh("meshes/Monkey.obj");
	monkey1.loadTexture("textures/fur.png");
	monkey2.loadMesh("meshes/Monkey.obj");
	monkey2.loadTexture("textures/fur.png");
	//monkey1.color = glm::vec4(1.f, 0.f, 0.f, 1.f);
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

	if (shouldRotate)
	{
		monkey1.rotate = glm::rotate(monkey1.rotate, deltaTime * (glm::pi<float>() / 4.f), glm::vec3(0.f, 1.f, 0.f));
	}

	if (wKeyDown)
	{
		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(0.f, deltaTime * 1.f, 0.f));
	}

	if (aKeyDown)
	{
		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(-deltaTime * 1.f, 0.f, 0.f));
	}

	if (sKeyDown)
	{
		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(0.f, -deltaTime * 1.f, 0.f));
	}

	if (dKeyDown)
	{
		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(deltaTime * 1.f, 0.f, 0.f));
	}

	if (zKeyDown)
	{
		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(0.f, 0.f, deltaTime * 1.f));
	}

	if (xKeyDown)
	{
		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(0.f, 0.f, -deltaTime * 1.f));
	}

	if (pKeyDown)
	{
		monkey1.scale += deltaTime * 1.f;
	}

	if (oKeyDown)
	{
		monkey1.scale -= deltaTime * 1.f;
	}

	monkey1.transform = monkey1.translate * monkey1.rotate * glm::scale(glm::mat4(), glm::vec3(monkey1.scale));
}

void Game::draw()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render stuff
	monkey1.draw(phong, cameraTransform, cameraProjection);
	monkey2.draw(phong, cameraTransform, cameraProjection);

	glutSwapBuffers();
}

void Game::keyboardDown(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
	case 27: // esc key
	case 'q':
		exit(1);
		break;
	case 'w':
		wKeyDown = true;
		break;
	case 'a':
		aKeyDown = true;
		break;
	case 's':
		sKeyDown = true;
		break;
	case 'd':
		dKeyDown = true;
		break;
	case 'z':
		zKeyDown = true;
		break;
	case 'x':
		xKeyDown = true;
		break;
	case 'o':
		oKeyDown = true;
		break;
	case 'p':
		pKeyDown = true;
		break;
	case 't':
		std::cout << "Total elapsed time: " << updateTimer->getCurrentTime() / 1000.f << std::endl;
		break;
	default:
		break;
	}
}

void Game::keyboardUp(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
	case 'r':
		shouldRotate = !shouldRotate;
		break;
	case 'w':
		wKeyDown = false;
		break;
	case 'a':
		aKeyDown = false;
		break;
	case 's':
		sKeyDown = false;
		break;
	case 'd':
		dKeyDown = false;
		break;
	case 'z':
		zKeyDown = false;
		break;
	case 'x':
		xKeyDown = false;
		break;
	case 'o':
		oKeyDown = false;
		break;
	case 'p':
		pKeyDown = false;
		break;
	default:
		break;
	}
}

void Game::mouseClicked(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			//handle left click
			break;
		case GLUT_RIGHT_BUTTON:
			// handle right click
			break;
		case GLUT_MIDDLE_BUTTON:
			// handle middle click
			break;
		default:
			break;
		}
	}
}

void Game::mouseMoved(int x, int y)
{
}