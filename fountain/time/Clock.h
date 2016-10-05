#ifndef _FEI_CLOCK_H_
#define _FEI_CLOCK_H_

#include "base/basedef.h"
#include "time/Time.h"

namespace fei {

class Clock
{
public:
	Clock();
	~Clock();

	void init();
	void init(Clock* mClock);

	void setMasterClock(Clock* mClock);

	void tick();

	double getTime();
	double getDeltaTime();
	long long getFrameCount();

	void setTimeScale(double tScale);
	double getTimeScale();
	void zoomTimeScale(double zoom);

	void play();
	void pause();
	void resume();
	void stop();

	bool isPlay();
	void setPlay(bool isplay);

	bool isStop();

	void switchPlayAndPause();

	void setTickCallback(std::function<void()> callback);

private:
	double calculateDeltaTime();

	double _totalTime;
	double _deltaTime;
	double _timeScale;

	long long _frameCount;

	bool _isMaster;
	bool _isPlay;
	bool _isStop;

	Clock* _masterClock;

	std::function<void()> _tickCallback;
};

} // namespace fei

inline void fei::Clock::tick()
{
	_deltaTime = calculateDeltaTime();
	if (_isPlay) {
		_totalTime += _deltaTime;
		_frameCount++;
		if (_tickCallback) {
			_tickCallback();
		}
	}
}

inline double fei::Clock::getTime()
{
	return _totalTime;
}

inline double fei::Clock::getDeltaTime()
{
	return _deltaTime;
}

inline long long fei::Clock::getFrameCount()
{
	return _frameCount;
}

inline double fei::Clock::calculateDeltaTime()
{
	double result = 0.0;
	if (_isPlay) {
		if (_isMaster) {
			result = fei::Time::getInstance()->getDeltaTime();
		} else {
			result = _masterClock->getDeltaTime();	
		}
		if (_timeScale != 1.0) {
			result *= _timeScale;
		}
	}
	return result;
}

inline bool fei::Clock::isPlay()
{
	return _isPlay;
}

inline bool fei::Clock::isStop()
{
	return _isStop;
}

#endif // _FEI_CLOCK_H_
