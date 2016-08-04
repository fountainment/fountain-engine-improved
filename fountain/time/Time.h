#ifndef _FEI_TIME_H_
#define _FEI_TIME_H_

#include "base/basedef.h"
#include "base/ModuleBase.h"

namespace fei {

class Clock;

class Time : public ModuleBase
{
public:
	bool init() override;
	void destroy() override;

	void executeBeforeFrame() override;
	void executeAfterFrame() override;

	double getTime();
	double getDeltaTime();
	long long getFrame();

	void littleSleep();
	double calcCurTime();
	double getFps();

	void addClock(Clock* pobj);
	void delClock(Clock* pobj);

	void setUseIdealTime(bool useIdealTime);

	static Time* getInstance();

private:
	Time();

	double _initTime;
	double _curTime;
	double _lastTime;
	double _deltaTime;
	double _defaultFps;
	double _defaultSpf;
	double _idealCurTime;
	long long _totalFrame;
	bool _useIdealTime;

	std::queue<double> _frameTimeQueue;
	std::list<Clock*> _clockList;

	static Time *instance_;
};

} // namespace fei

inline double fei::Time::getTime()
{
	return _useIdealTime ? _idealCurTime : _curTime;
}

inline double fei::Time::getDeltaTime()
{
	return _useIdealTime ? _defaultSpf : _deltaTime;
}

inline long long fei::Time::getFrame()
{
	return _totalFrame;
}

#endif // _FEI_TIME_H_
