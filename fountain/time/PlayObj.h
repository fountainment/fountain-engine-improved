#if !defined(_FEI_PLAYOBJ_H_)
#define _FEI_PLAYOBJ_H_

#include "time/Clock.h"

namespace fei {

class PlayObj
{
public:
	PlayObj();
	bool isLoop();
	void setLoop(bool isloop);

private:
	bool _isLoop;

protected:
	Clock playClock;
};

}

#endif