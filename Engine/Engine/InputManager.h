#pragma once
#include <glm\glm.hpp>

enum MouseButtons
{
	LEFT_MOUSE_BUTTON,
	MIDDLE_MOUSE_BUTTON, 
	RIGHT_MOUSE_BUTTON
};

enum Keys
{
	Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	Tilde,
	Minus,
	Equals,
	Backspace,
	Esc,
	Tab,
	LeftBracket,
	RightBracket,
	BackSlash,
	Semicolon,
	Quotation,
	Enter,
	Comma,
	Period,
	ForwardSlash,
	LeftArrow,
	Spacebar,
	UpArrow,
	RightArrow,
	DownArrow,
	PageUp,
	PageDown,
	Home,
	End,
	Insert,
	Delete,
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	NUM_KEYS
};

enum Modifiers
{
	Shift,
	Control,
	Alt
};

class InputManager
{
public:
	static void keyboardDown(unsigned char key, int mouseX, int mouseY);
	static void specialKeyboardDown(int key, int mouseX, int mouseY);
	static void keyboardUp(unsigned char key, int mouseX, int mouseY);
	static void specialKeyboardUp(int key, int mouseX, int mouseY);
	static void mouseClicked(int button, int state, int x, int y);
	static void mouseMoved(int x, int y);

	static bool isModifierDown(Modifiers mod);

	static bool isKeyDown(Keys key);
	static bool isKeyDownThisFrame(Keys key);
	static bool isKeyUpThisFrame(Keys key);

	static glm::vec2 getMousePosition();

	static bool isMouseButtonDown(MouseButtons button);
	static bool isMouseButtonDownThisFrame(MouseButtons button);
	static bool isMouseButtonUpThisFrame(MouseButtons button);

	static void reset();

private:
	InputManager() {};

	static glm::vec2 mousePos;
	static bool mouseButtonsDown[3];
	static bool mouseButtonsDownThisFrame[3];
	static bool mouseButtonsUpThisFrame[3];

	static bool keysDown[(int)NUM_KEYS];
	static bool keysDownThisFrame[(int)NUM_KEYS];
	static bool keysUpThisFrame[(int)NUM_KEYS];

	static bool modifiersDown[3];

	static Keys convertSpecialKeyToEnum(int key);
	static Keys convertAsciiKeyToEnum(unsigned char key);

	static void setModifiers();
};