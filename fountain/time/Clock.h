#if !defined(_FEI_CLOCK_H_)
#define _FEI_CLOCK_H_

namespace fei {

class Clock
{
public:
	Clock();

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

private:
	double calculateDeltaTime();

	double totalTime;
	double deltaTime;
	double timeScale;

	long long frameCount;

	bool _isMaster;
	bool _isPlay;
	bool _isStop;

	Clock* masterClock;
};

} // namespace fei

#endif // _FEI_CLOCK_H_
