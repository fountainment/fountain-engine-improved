#include "time/Clock.h"

#include "time/Time.h"

using fei::Clock;

Clock::Clock()
: _totalTime(0.0),
  _deltaTime(0.0),
  _timeScale(1.0),
  _frameCount(0),
  _isMaster(true),
  _isPlay(true),
  _isStop(false),
  _masterClock(nullptr)
{
	fei::Time::getInstance()->addClock(this);
}

Clock::~Clock()
{
	fei::Time::getInstance()->delClock(this);
}

void Clock::init()
{
	_totalTime = 0.0;
	_frameCount = 0;
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
	_masterClock = mClock;
	if (!_masterClock) {
		_isMaster = true;
	} else {
		_isMaster = false;
	}
}

void Clock::setTimeScale(double tScale)
{
	_timeScale = tScale;
}

double Clock::getTimeScale()
{
	return _timeScale;
}

void Clock::zoomTimeScale(double zoom)
{
	_timeScale *= zoom;
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
	_totalTime = 0.0;
	_frameCount = 0;
}

void Clock::setPlay(bool isplay)
{
	_isPlay = isplay;
}

void Clock::switchPlayAndPause()
{
	if (isPlay()) {
		pause();
	} else {
		resume();
	}
}
