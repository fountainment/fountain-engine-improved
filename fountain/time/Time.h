#if !defined(_FEI_TIME_H_)
#define _FEI_TIME_H_

#include "../base/ModuleBase.h"

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

	static Time* getInstance();
private:
	Time();

	double initTime;
	double curTime;
	double lastTime;
	double deltaTime;
	long long totalFrame;

	static Time *instance;
};

}

#endif
