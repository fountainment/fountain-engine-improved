#ifndef _FEI_TIMER_H_
#define _FEI_TIMER_H_

#include "time/PlayObj.h"

namespace fei {

class Timer : public PlayObj
{
public:
	Timer();

	double getInterval();
	void setInterval(double interval);

	double getRemainTime();
	double getRemainTimePercentage();

private:
	void setRemainTime(double remainTime);

	void timerUpdate();

	double _interval;
	double _remainTime;
};

inline double Timer::getInterval()
{
	return _interval;
}

inline double Timer::getRemainTime()
{
	return _remainTime;
}

inline void Timer::setRemainTime(double remainTime)
{
	_remainTime = remainTime;
}

} // namespace fei

#endif // _FEI_TIMER_H_
