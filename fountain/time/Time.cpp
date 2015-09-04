#include "Time.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using fei::Time;

Time *Time::instance = nullptr;

Time* Time::getInstance()
{
	if (!instance) {
		instance = new Time();
	}
	return instance;
}

Time::Time()
: initTime(0.0),
  curTime(0.0),
  lastTime(0.0),
  deltaTime(0.0),
  totalFrame(0)
{
}

bool Time::init()
{
	if (GL_FALSE == glfwInit()) {
		return false;
	} else {
		initTime = glfwGetTime();
	}
	return true;
}

void Time::destroy()
{
	glfwTerminate();
}

void Time::executeBeforeFrame()
{
	lastTime = curTime;
	curTime = glfwGetTime() - initTime;
	deltaTime = curTime - lastTime;
	if (deltaTime > 0.33 || deltaTime < 0.0) {
		deltaTime = 0.0;
	}
}

void Time::executeAfterFrame()
{
	totalFrame++;
}

double Time::getTime()
{
	return curTime;
}

double Time::getDeltaTime()
{
	return deltaTime;
}

long long Time::getFrame()
{
	return totalFrame;
}
