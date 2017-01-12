#include "Timer.h"

using fei::Timer;

Timer::Timer()
: _interval(0.0),
  _remainTime(0.0)
{
	stop();
	setTickCallback(std::bind(&Timer::timerUpdate, this));
}

void Timer::setInterval(double interval)
{
	_interval = interval;
}

double Timer::getRemainTimePercentage()
{
	return getRemainTime() / getInterval();
}

void Timer::timerUpdate()
{
	setRemainTime(getInterval() - getClock()->getTime());
	if (getRemainTime() < 0.0) {
		setRemainTime(0.0f);
		stop();
	}
}
