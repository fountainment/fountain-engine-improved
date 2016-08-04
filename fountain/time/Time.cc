#include "time/Time.h"

#if defined(__linux) // Linux
	#if !defined(_BSD_SOURCE)
		#define _BSD_SOURCE
	#endif
	#include <sys/time.h>
	#include <unistd.h>
#endif // Linux end

#if defined(_WIN32) // Win32
	#include <windows.h>
#endif // Win32 end

#include "time/Clock.h"

#include <GLFW/glfw3.h>

#if defined(__linux) // Linux
	constexpr double littleSleepTime = 0.000001;

	inline void sysLittleSleep()
	{
		usleep(1);
	}
#endif // Linux end

#if defined(_WIN32) // Win32
	constexpr double littleSleepTime = 0.001;

	inline void sysLittleSleep()
	{
		timeBeginPeriod(1);
		Sleep(1);
		timeEndPeriod(1);
	}
#endif // Win32 end

using fei::Time;

Time *Time::instance_ = nullptr;

Time* Time::getInstance()
{
	if (!instance_) {
		instance_ = new Time();
	}
	return instance_;
}

Time::Time()
: _initTime(0.0),
  _curTime(0.0),
  _lastTime(0.0),
  _deltaTime(0.0),
  _defaultFps(60.0),
  _defaultSpf(1.0 / _defaultFps),
  _idealCurTime(0.0),
  _totalFrame(0),
  _useIdealTime(false)
{
}

bool Time::init()
{
	if (GLFW_FALSE == glfwInit()) {
		return false;
	} else {
		glfwSetTime(0.0);
		_initTime = 0.0;
	}
	return true;
}

void Time::destroy()
{
	glfwTerminate();
}

void Time::executeBeforeFrame()
{
	_lastTime = _curTime;
	_curTime = calcCurTime();
	_idealCurTime = _initTime + (_totalFrame + 1) * _defaultSpf;
	_deltaTime = _curTime - _lastTime;

	while (_deltaTime < _defaultSpf - littleSleepTime) {
		littleSleep();
		_curTime = calcCurTime();
		_deltaTime = _curTime - _lastTime;
	}
	if (_deltaTime > _defaultSpf * 10.0 || _deltaTime < 0.0) {
		_deltaTime = 0.0;
	}

	for (auto clock : _clockList) {
		clock->tick();
	}
}

void Time::executeAfterFrame()
{
	auto &q = _frameTimeQueue;
	q.push(_curTime);
	while (q.back() - q.front() > 1.0) {
		q.pop();
	}
	_totalFrame++;
}

void Time::littleSleep()
{
	sysLittleSleep();
}

double fei::Time::calcCurTime()
{
	return glfwGetTime() - _initTime;
}

double Time::getFps()
{
	auto &q = _frameTimeQueue;
	double frameNum = q.size() - 1;
	if (frameNum <= 0) {
		return 0.0;
	}
	double frameDuration = q.back() - q.front();
	return frameNum / frameDuration;
}

void Time::addClock(fei::Clock* clock)
{
	_clockList.push_back(clock);
}

void Time::delClock(fei::Clock* clock)
{
	_clockList.remove(clock);
}

void Time::setUseIdealTime(bool useIdealTime)
{
	_useIdealTime = useIdealTime;
}
