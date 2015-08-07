#if !defined(_FEI_TIME_H_)
#define _FEI_TIME_H_

#include "../base/ModuleBase.h"

namespace fei {

class Time : public ModuleBase
{
public:
	bool init();
	void destroy();

	double getTime();

	static Time* getInstance();
private:
	Time();

	double initTime;

	static Time *instance;
};

}

#endif
