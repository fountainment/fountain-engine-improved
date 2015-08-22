#if !defined(_FEI_CLOCK_H_)
#define _FEI_CLOCK_H_

namespace fei {

class Clock
{
public:
	Clock();

	void init(Clock* mClock = nullptr);

	void tick();

	double getTime();
	double getDeltaTime();
	long long getFrameCount();

	void pause();
	void resume();

private:
	double calculateDeltaTime();

	double totalTime;
	double deltaTime;

	long long frameCount;

	bool _isMaster;
	bool _isPlay;

	Clock* masterClock;
};

}

#endif
