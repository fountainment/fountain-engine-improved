#include "Time.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#if defined(__linux) // Linux
	#if !defined(_BSD_SOURCE)
		#define _BSD_SOURCE
	#endif
	#include <sys/time.h>
	#include <unistd.h>

	const double littleSleepTime = 0.000001;

	inline void sysLittleSleep()
	{
		usleep(1);
	}
#endif // Linux end

#if defined(_WIN32) // Win32
	#include <time.h>
	#include <windows.h>

	const double littleSleepTime = 0.001;

	inline void sysLittleSleep()
	{
		//Sleep(1);
	}
#endif // Win32 end

using fei::Time;

Time *Time::instance = nullptr;

const double defaultFps = 60.0;
const double spf = 1.0 / defaultFps;

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
	curTime = calcCurTime();
	deltaTime = curTime - lastTime;
	while (deltaTime < spf - littleSleepTime) {
		littleSleep();
		curTime = calcCurTime();
		deltaTime = curTime - lastTime;
	}
	if (deltaTime > spf * 10.0 || deltaTime < 0.0) {
		deltaTime = 0.0;
	}
}

void Time::executeAfterFrame()
{
	auto &q = frameTimeQueue;
	q.push(curTime);
	while (q.back() - q.front() > 1.0) {
		q.pop();
	}
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

void Time::littleSleep()
{
	sysLittleSleep();
}

double Time::calcCurTime()
{
	return glfwGetTime() - initTime;
}

double Time::getFps()
{
	auto &q = frameTimeQueue;
	double frameNum = q.size() - 1;
	if (frameNum <= 0) {
		return 0.0;
	}
	double frameDuration = q.back() - q.front();
	return frameNum / frameDuration;
}