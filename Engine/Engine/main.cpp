#include <GL\glew.h>
#include <GL\glut.h>
#include <GL\freeglut.h>
#include <iostream>
#include <memory>

#include "Game.h"
#include "InputManager.h"

const int FRAME_DELAY = 1000 / FRAMES_PER_SECOND;

std::shared_ptr<Game> game;

void DisplayCallbackFunction(void) 
{
	game->draw();
}

void KeyboardCallbackFunction(unsigned char key, int x, int y)
{
	InputManager::keyboardDown(key, x, y);
}

void KeyboardUpCallbackFunction(unsigned char key, int x, int y)
{
	InputManager::keyboardUp(key, x, y);
}

void TimerCallbackFunction(int value)
{
	game->update();

	glutPostRedisplay();
	glutTimerFunc(FRAME_DELAY, TimerCallbackFunction, 0);

	InputManager::reset();
}

void MouseClickCallbackFunction(int button, int state, int x, int y)
{
	InputManager::mouseClicked(button, state, x, y);
}

void MouseMotionCallbackFunction(int x, int y)
{
	InputManager::mouseMoved(x, y);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 2);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Tutorial");

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW could not be initialized." << std::endl;
		system("pause");
		return 0;
	}

	std::cout << "OpenGL version: " << glGetString(GL_VERSION)
		<< std::endl;

	// setup callback functions
	glutDisplayFunc(DisplayCallbackFunction);
	glutKeyboardFunc(KeyboardCallbackFunction);
	glutKeyboardUpFunc(KeyboardUpCallbackFunction);
	glutMouseFunc(MouseClickCallbackFunction);
	glutMotionFunc(MouseMotionCallbackFunction);
	glutTimerFunc(1, TimerCallbackFunction, 0);

	// initialize game
	game = std::make_shared<Game>();
	game->initializeGame();

	// start game
	glutMainLoop();

	return 0;
}