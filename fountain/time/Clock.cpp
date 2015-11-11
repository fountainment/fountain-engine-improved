#include "time/Clock.h"

#include "time/Time.h"

using fei::Clock;

Clock::Clock()
: totalTime(0.0),
  deltaTime(0.0),
  timeScale(1.0),
  frameCount(0),
  _isMaster(true),
  _isPlay(true),
  _isStop(false),
  masterClock(nullptr)
{
}

void Clock::init()
{
	totalTime = 0.0;
	frameCount = 0;
	_isPlay = true;
	_isStop = false;
}

void Clock::init(Clock* mClock)
{
	init();
	setMasterClock(mClock);
}

void Clock::setMasterClock(Clock* mClock)
{
	masterClock = mClock;
	if (!masterClock) {
		_isMaster = true;
	} else {
		_isMaster = false;
	}
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

void Clock::setTimeScale(double tScale)
{
	timeScale = tScale;
}

double Clock::getTimeScale()
{
	return timeScale;
}

void Clock::zoomTimeScale(double zoom)
{
	timeScale *= zoom;
}

void Clock::play()
{
	stop();
	resume();
}

void Clock::pause()
{
	_isPlay = false;
}

void Clock::resume()
{
	_isPlay = true;
	_isStop = false;
}

void Clock::stop()
{
	_isPlay = false;
	_isStop = true;
	totalTime = 0.0;
	frameCount = 0;
}

bool Clock::isPlay()
{
	return _isPlay;
}

void Clock::setPlay(bool isplay)
{
	_isPlay = isplay;
}

bool Clock::isStop()
{
	return _isStop;
}

void Clock::switchPlayAndPause()
{
	if (isPlay()) {
		pause();
	} else {
		resume();
	}
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
		if (timeScale != 1.0) {
			result *= timeScale;
		}
	}
	return result;
}
