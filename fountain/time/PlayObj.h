#ifndef _FEI_PLAYOBJ_H_
#define _FEI_PLAYOBJ_H_

#include "base/basedef.h"
#include "time/Clock.h"

namespace fei {

class PlayObj
{
public:
	PlayObj();
	virtual ~PlayObj() = default;

	bool isLoop();
	void setLoop(bool isloop);

	void play();
	void pause();
	void resume();
	void stop();

	bool isStop();
	bool isPlay();

	double getDeltaTime();

	Clock* getClock();
	void setMasterClock(Clock* clock);

	void setPlayCallback(std::function<void()> callback);
	void setPauseCallback(std::function<void()> callback);
	void setResumeCallback(std::function<void()> callback);
	void setStopCallback(std::function<void()> callback);
	void setTickCallback(std::function<void()> callback);

protected:
	virtual void afterPlay();
	virtual void afterPause();
	virtual void afterResume();
	virtual void afterStop();

private:
	bool _isLoop;
	Clock _playClock;

	std::function<void()> _playCallback;
	std::function<void()> _pauseCallback;
	std::function<void()> _resumeCallback;
	std::function<void()> _stopCallback;
};

} // namespace fei

#endif // _FEI_PLAYOBJ_H_
