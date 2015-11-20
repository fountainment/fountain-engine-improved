#if !defined(_FEI_TIME_H_)
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

	static Time* getInstance();

private:
	Time();

	double initTime;
	double curTime;
	double lastTime;
	double deltaTime;
	long long totalFrame;

	std::queue<double> frameTimeQueue;
	std::list<Clock*> _clockList;

	static Time *instance;
};

} // namespace fei

#endif // _FEI_TIME_H_
