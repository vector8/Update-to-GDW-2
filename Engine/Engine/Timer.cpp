#include "Timer.h"
#include <GLFW\glfw3.h>

Timer::Timer()
{
	previousTime = glfwGetTime();
	tick();
}

Timer::~Timer()
{
}

// update the timer
float Timer::tick()
{
	currentTime = glfwGetTime();
	elapsedTime = currentTime - previousTime;
	previousTime = currentTime;
	return elapsedTime;
}

// return the delta time in milliseconds
float Timer::getElapsedTimeMS()
{
	return elapsedTime * 1000.f;
}

// return the delta time in seconds
float Timer::getElapsedTimeSeconds()
{
	return elapsedTime;
}

// get time since program start
float Timer::getCurrentTime()
{
	return currentTime;
}