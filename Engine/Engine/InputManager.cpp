#include "InputManager.h"
#include <GL\glut.h>
#include <cctype>
#include <iostream>

glm::vec2 InputManager::mousePos;
bool InputManager::mouseButtonsDown[3];
bool InputManager::mouseButtonsDownThisFrame[3];
bool InputManager::mouseButtonsUpThisFrame[3];
bool InputManager::keysDown[(int)NUM_KEYS];
bool InputManager::keysDownThisFrame[(int)NUM_KEYS];
bool InputManager::keysUpThisFrame[(int)NUM_KEYS];
bool InputManager::modifiersDown[3];

void InputManager::keyboardDown(unsigned char key, int mouseX, int mouseY)
{
	std::cout << key << std::endl;
	setModifiers();

	Keys keyEnum = convertAsciiKeyToEnum(key);
	if (keyEnum == Keys::NUM_KEYS)
		return;

	if (!keysDown[(int)keyEnum])
	{
		keysDownThisFrame[(int)keyEnum] = true;
	}
	keysDown[(int)keyEnum] = true;
}

void InputManager::specialKeyboardDown(int key, int mouseX, int mouseY)
{
	setModifiers();

	Keys keyEnum = convertSpecialKeyToEnum(key);
	if (keyEnum == Keys::NUM_KEYS)
		return;

	if (!keysDown[(int)keyEnum])
	{
		keysDownThisFrame[(int)keyEnum] = true;
	}
	keysDown[(int)keyEnum] = true;
}

void InputManager::keyboardUp(unsigned char key, int mouseX, int mouseY)
{
	setModifiers();

	Keys keyEnum = convertAsciiKeyToEnum(key);
	if (keyEnum == Keys::NUM_KEYS)
		return;

	keysDown[(int)keyEnum] = false;
	keysUpThisFrame[(int)keyEnum] = true;

}

void InputManager::specialKeyboardUp(int key, int mouseX, int mouseY)
{
	setModifiers();

	Keys keyEnum = convertSpecialKeyToEnum(key);
	if (keyEnum == Keys::NUM_KEYS)
		return;

	keysDown[(int)keyEnum] = false;
	keysUpThisFrame[(int)keyEnum] = true;

}

void InputManager::mouseClicked(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		mouseButtonsDown[button] = true;
		mouseButtonsDownThisFrame[button] = true;
	}
	else if (state == GLUT_UP)
	{
		mouseButtonsDown[button] = false;
		mouseButtonsUpThisFrame[button] = true;
	}

	mousePos.x = x;
	mousePos.y = y;

	setModifiers();
}

void InputManager::mouseMoved(int x, int y)
{
	mousePos.x = x;
	mousePos.y = y;

	setModifiers();
}

bool InputManager::isModifierDown(Modifiers mod)
{
	return modifiersDown[(int)mod];
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
	for (int i = 0; i < 3; i++)
	{
		mouseButtonsDownThisFrame[i] = false;
		mouseButtonsUpThisFrame[i] = false;
	}

	for (int i = 0; i < (int)Keys::NUM_KEYS; i++)
	{
		keysDownThisFrame[i] = false;
		keysUpThisFrame[i] = false;
	}
}

Keys InputManager::convertSpecialKeyToEnum(int key)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		return Keys::F1;
	case GLUT_KEY_F2:
		return Keys::F2;
	case GLUT_KEY_F3:
		return Keys::F3;
	case GLUT_KEY_F4:
		return Keys::F4;
	case GLUT_KEY_F5:
		return Keys::F5;
	case GLUT_KEY_F6:
		return Keys::F6;
	case GLUT_KEY_F7:
		return Keys::F7;
	case GLUT_KEY_F8:
		return Keys::F8;
	case GLUT_KEY_F9:
		return Keys::F9;
	case GLUT_KEY_F10:
		return Keys::F10;
	case GLUT_KEY_F11:
		return Keys::F11;
	case GLUT_KEY_F12:
		return Keys::F12;
	case GLUT_KEY_LEFT:
		return Keys::LeftArrow;
	case GLUT_KEY_UP:
		return Keys::UpArrow;
	case GLUT_KEY_RIGHT:
		return Keys::RightArrow;
	case GLUT_KEY_DOWN:
		return Keys::DownArrow;
	case GLUT_KEY_PAGE_UP:
		return Keys::PageUp;
	case GLUT_KEY_PAGE_DOWN:
		return Keys::PageDown;
	case GLUT_KEY_HOME:
		return Keys::Home;
	case GLUT_KEY_END:
		return Keys::End;
	case GLUT_KEY_INSERT:
		return Keys::Insert;
	default:
		std::cout << "Error convertSpecialKeyToEnum: Can't find key " << key << std::endl;
		return Keys::NUM_KEYS;
	}
}

Keys InputManager::convertAsciiKeyToEnum(unsigned char key)
{
	unsigned char lowerKey = std::tolower(key);

	switch (lowerKey)
	{
	case 48:
	case 41:
		return Keys::Num0;
	case 49:
	case 33:
		return Keys::Num1;
	case 50:
	case 64:
		return Keys::Num2;
	case 51:
	case 35:
		return Keys::Num3;
	case 52:
	case 36:
		return Keys::Num4;
	case 53:
	case 37:
		return Keys::Num5;
	case 54:
	case 94:
		return Keys::Num6;
	case 55:
	case 38:
		return Keys::Num7;
	case 56:
	case 42:
		return Keys::Num8;
	case 57:
	case 40:
		return Keys::Num9;
	case 97:
		return Keys::A;
	case 98:
		return Keys::B;
	case 99:
		return Keys::C;
	case 100:
		return Keys::D;
	case 101:
		return Keys::E;
	case 102:
		return Keys::F;
	case 103:
		return Keys::G;
	case 104:
		return Keys::H;
	case 105:
		return Keys::I;
	case 106:
		return Keys::J;
	case 107:
		return Keys::K;
	case 108:
		return Keys::L;
	case 109:
		return Keys::M;
	case 110:
		return Keys::N;
	case 111:
		return Keys::O;
	case 112:
		return Keys::P;
	case 113:
		return Keys::Q;
	case 114:
		return Keys::R;
	case 115:
		return Keys::S;
	case 116:
		return Keys::T;
	case 117:
		return Keys::U;
	case 118:
		return Keys::V;
	case 119:
		return Keys::W;
	case 120:
		return Keys::X;
	case 121:
		return Keys::Y;
	case 122:
		return Keys::Z;
	case 96:
	case 126:
		return Keys::Tilde;
	case 45:
	case 95:
		return Keys::Minus;
	case 43:
	case 61:
		return Keys::Equals;
	case 8:
		return Keys::Backspace;
	case 27:
		return Keys::Esc;
	case 9:
		return Keys::Tab;
	case 91:
	case 123:
		return Keys::LeftBracket;
	case 93:
	case 125:
		return Keys::RightBracket;
	case 92:
	case 124:
		return Keys::BackSlash;
	case 58:
	case 59:
		return Keys::Semicolon;
	case 34:
	case 39:
		return Keys::Quotation;
	case 13:
		return Keys::Enter;
	case 44:
	case 60:
		return Keys::Comma;
	case 46:
	case 62:
		return Keys::Period;
	case 47:
	case 63:
		return Keys::ForwardSlash;
	case 32:
		return Keys::Spacebar;
	case 127:
		return Keys::Delete;
	default:
		std::cout << "Error convertAsciiKeyToEnum: Can't find key " << lowerKey << std::endl;
		return Keys::NUM_KEYS;
	}
}

void InputManager::setModifiers()
{
	modifiersDown[(int)Modifiers::Shift] = (glutGetModifiers() & GLUT_ACTIVE_SHIFT);
	modifiersDown[(int)Modifiers::Control] = (glutGetModifiers() & GLUT_ACTIVE_CTRL);
	modifiersDown[(int)Modifiers::Alt] = (glutGetModifiers() & GLUT_ACTIVE_ALT);
}