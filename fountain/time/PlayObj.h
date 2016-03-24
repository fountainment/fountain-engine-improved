#ifndef _FEI_PLAYOBJ_H_
#define _FEI_PLAYOBJ_H_

#include "time/Clock.h"

namespace fei {

class PlayObj
{
public:
	PlayObj();

	bool isLoop();
	void setLoop(bool isloop);

	void play();
	void pause();
	void stop();

	bool isStop();
	bool isPlay();

	double getDeltaTime();

	void setMasterClock(Clock* clock);

private:
	bool _isLoop;
	Clock _playClock;
};

} // namespace fei

#endif // _FEI_PLAYOBJ_H_
