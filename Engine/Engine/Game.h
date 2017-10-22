#pragma once

#include "Timer.h"
#include "ShaderProgram.h"
#include "GameObject.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FRAMES_PER_SECOND 60

class Game
{
public:
	Game();
	~Game();

	void initializeGame();
	void update();
	void draw();

	// Input callback functions
	void keyboardDown(unsigned char key, int mouseX, int mouseY);
	void keyboardUp(unsigned char key, int mouseX, int mouseY);
	void mouseClicked(int button, int state, int x, int y);
	void mouseMoved(int x, int y);

	// Data Member
	Timer* updateTimer = nullptr;
	GameObject monkey1, monkey2;
	ShaderProgram passThrough;
	ShaderProgram phongNoTexture;
	ShaderProgram phong;

	glm::mat4 cameraTransform;
	glm::mat4 cameraProjection;

private:
	bool shouldRotate = false;
	bool wKeyDown = false;
	bool aKeyDown = false;
	bool sKeyDown = false;
	bool dKeyDown = false;
	bool zKeyDown = false;
	bool xKeyDown = false;
	bool pKeyDown = false;
	bool oKeyDown = false;
};