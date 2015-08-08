#include "Clock.h"
#include "Time.h"

using fei::Clock;

Clock::Clock()
: totalTime(0.0),
  deltaTime(0.0),
  frameCount(0),
  _isMaster(true),
  _isPlay(true),
  masterClock(nullptr)
{
}

void Clock::init(Clock* mClock)
{
	masterClock = mClock;
	totalTime = 0.0;
	if (!masterClock) {
		_isMaster = true;
	} else {
		_isMaster = false;
	}
	_isPlay = true;
}

void Clock::tick()
{
	deltaTime = calculateDeltaTime();
	if (_isPlay) {
		totalTime += deltaTime;
		frameCount++;
	}
}

double Clock::getTime()
{
	return totalTime;
}

double Clock::getDeltaTime()
{
	return deltaTime;
}

long long Clock::getFrameCount()
{
	return frameCount;
}

void Clock::pause()
{
	_isPlay = false;
}

void Clock::resume()
{
	_isPlay = true;
}

double Clock::calculateDeltaTime()
{
	double result = 0.0;
	if (_isPlay) {
		if (_isMaster) {
			result = Time::getInstance()->getDeltaTime();
		} else {
			result = masterClock->getDeltaTime();	
		}
	}
	return result;
}
