#include "InputManager.h"
#include <cctype>
#include <iostream>
#include <GLFW\glfw3.h>

glm::vec2 InputManager::mousePos;
std::unordered_map<int, bool> InputManager::mouseButtonsDown;
std::unordered_map<int, bool> InputManager::mouseButtonsDownThisFrame;
std::unordered_map<int, bool> InputManager::mouseButtonsUpThisFrame;
std::unordered_map<int, bool> InputManager::keysDown;
std::unordered_map<int, bool> InputManager::keysDownThisFrame;
std::unordered_map<int, bool> InputManager::keysUpThisFrame;

void InputManager::keyEvent(int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
	{
		keysDown[key] = true;
		keysDownThisFrame[key] = true;
	}
			break;
	case GLFW_RELEASE:
	{
		keysDown[key] = false;
		keysUpThisFrame[key] = true;
	}
		break;
	case GLFW_REPEAT:

		break;
	default:
		break;
	}
}

void InputManager::mouseButtonEvent(int button, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
	{
		mouseButtonsDown[button] = true;
		mouseButtonsDownThisFrame[button] = true;
	}
	break;
	case GLFW_RELEASE:
	{
		mouseButtonsDown[button] = false;
		mouseButtonsUpThisFrame[button] = true;
	}
	break;
	default:
		break;
	}
}

void InputManager::mouseMoved(float x, float y)
{
	mousePos.x = x;
	mousePos.y = y;
}

bool InputManager::isKeyDown(Keys key)
{
	return keysDown[(int)key];
}

bool InputManager::isKeyDownThisFrame(Keys key)
{
	return keysDownThisFrame[(int)key];
}

bool InputManager::isKeyUpThisFrame(Keys key)
{
	return keysUpThisFrame[(int)key];
}

glm::vec2 InputManager::getMousePosition()
{
	return mousePos;
}

bool InputManager::isMouseButtonDown(MouseButtons button)
{
	return mouseButtonsDown[(int)button];
}

bool InputManager::isMouseButtonDownThisFrame(MouseButtons button)
{
	return mouseButtonsDownThisFrame[(int)button];
}

bool InputManager::isMouseButtonUpThisFrame(MouseButtons button)
{
	return mouseButtonsUpThisFrame[(int)button];
}

void InputManager::reset()
{
	for (auto itr = mouseButtonsDownThisFrame.begin(); itr != mouseButtonsDownThisFrame.end(); itr++)
	{
		itr->second = false;
	}

	for (auto itr = mouseButtonsUpThisFrame.begin(); itr != mouseButtonsUpThisFrame.end(); itr++)
	{
		itr->second = false;
	}

	for (auto itr = keysDownThisFrame.begin(); itr != keysDownThisFrame.end(); itr++)
	{
		itr->second = false;
	}

	for (auto itr = keysUpThisFrame.begin(); itr != keysUpThisFrame.end(); itr++)
	{
		itr->second = false;
	}
}