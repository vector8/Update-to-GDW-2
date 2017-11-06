#pragma once

#include "Timer.h"
#include "ShaderProgram.h"
#include "GameObject.h"
#include <memory>
#include "InputManager.h"

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 512
#define FRAMES_PER_SECOND 60

class Game
{
public:
	Game();
	~Game();

	void initializeGame();
	void update();
	void draw();
	void mainLoop();

	// Data Member
	std::shared_ptr<Timer> updateTimer = nullptr;
	GameObject monkey1, monkey2;
	ShaderProgram passThrough;
	ShaderProgram phongNoTexture;
	ShaderProgram phong;
	ShaderProgram uvMap;
	ShaderProgram noisemapShader;
	std::vector<Light> pointLights;

	GLuint vaoNoise = 0;
	GLuint vboVertices = 0;
	GLuint vboColor = 0;
	std::vector<float> vertexData;
	std::vector<float> colorData;

	glm::mat4 cameraTransform;
	glm::mat4 cameraTranslate;
	glm::mat4 cameraRotate;
	glm::mat4 cameraProjection;

private:
	bool shouldRotate = false;
};