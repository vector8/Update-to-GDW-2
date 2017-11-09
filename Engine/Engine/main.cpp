#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <memory>

#include "Game.h"
#include "InputManager.h"
#include <Windows.h>

const int FRAME_DELAY = 1000 / FRAMES_PER_SECOND;

std::shared_ptr<Game> game;

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputManager::keyEvent(key, scancode, action, mods);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	InputManager::mouseButtonEvent(button, action, mods);
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	InputManager::mouseMoved((float)xpos, (float)ypos);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	InputManager::scrollEvent((float)xoffset, (float)yoffset);
}

int main(int argc, char **argv)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tutorial", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW could not be initialized." << std::endl;
		system("pause");
		return 0;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	std::cout << "OpenGL version: " << glGetString(GL_VERSION)
		<< std::endl;

	// setup callback functions
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetKeyCallback(window, keyboardCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetScrollCallback(window, scrollCallback);

	// initialize game
	game = std::make_shared<Game>();
	game->initializeGame();

	// start game
	while (!glfwWindowShouldClose(window))
	{
		game->mainLoop();
		InputManager::reset();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}