#ifndef _FEI_TIME_H_
#define _FEI_TIME_H_

#include "base/basedef.h"
#include "base/ModuleBase.h"

#include <GLFW/glfw3.h>

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

	static Time* getInstance();

private:
	Time();

	double _initTime;
	double _curTime;
	double _lastTime;
	double _deltaTime;
	long long _totalFrame;

	std::queue<double> _frameTimeQueue;
	std::list<Clock*> _clockList;

	static Time *instance_;
};

} // namespace fei

inline double fei::Time::getDeltaTime()
{
	return _deltaTime;
}

inline double fei::Time::calcCurTime()
{
	return glfwGetTime() - _initTime;
}

#endif // _FEI_TIME_H_
