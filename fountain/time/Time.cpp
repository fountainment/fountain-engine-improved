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
	if (_isLoad) return true;
	_isLoad = true;
	if (GL_FALSE == glfwInit()) {
		_isLoad = false;
	} else {
		initTime = glfwGetTime();
	}
	return _isLoad;
}

void Time::destroy()
{
	if (!_isLoad) return;
	glfwTerminate();
	_isLoad = false;
}

void Time::executeBeforeFrame()
{
	lastTime = curTime;
	curTime = glfwGetTime() - initTime;
	deltaTime = curTime - lastTime;
	//for test
	if (deltaTime > 0.033 || deltaTime < 0.0) {
		deltaTime = 0.0166666666;
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
