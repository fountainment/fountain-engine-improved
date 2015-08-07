#include "Time.h"
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

double Time::getTime()
{
	double t = glfwGetTime() - initTime;
	return t;
}

