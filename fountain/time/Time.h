#if !defined(_FEI_TIME_H_)
#define _FEI_TIME_H_

#include "base/ModuleBase.h"
#include "base/basedef.h"

namespace fei {

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

	static Time* getInstance();

private:
	Time();

	double initTime;
	double curTime;
	double lastTime;
	double deltaTime;
	long long totalFrame;

	std::queue<double> frameTimeQueue;

	static Time *instance;
};

}

#endif
