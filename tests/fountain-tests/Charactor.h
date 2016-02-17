#if !defined(_CHARACTOR_H_)
#define _CHARACTOR_H_

#include "fountain.h"
#include "util/PhysicsAnime.h"
#include "util/FSM.h"

class CharFSM : public fut::FSM
{
	virtual void outputSignal(int signal) override
	{
		std::printf("output: %d %s\n", signal, getStateName(getState()).c_str());
	};
};

class Charactor : public fei::RenderObj, public fut::FSM
{
public:
	Charactor();

	virtual void drawIt() override;
	virtual void init() override;
	virtual void destroy() override;
	virtual void update() override;

	void setSpeed(const fei::Vec2& drct, float sp);

	void attack();

	virtual void outputSignal(int signal) override;

	fei::Clock charClock;

private:
	fei::Vec2 speed;
	fei::Body *body;

	fei::FrameAnime *curAnime;
	fei::FrameAnime standAnime[4];
	fei::FrameAnime walkAnime[4];
	fei::FrameAnime runAnime[4];
	fut::CollisionFrameAnime atk1Anime;
	fut::CollisionFrameAnime atk2Anime;
	fut::CollisionFrameAnime atk3Anime;
	//TODO: anime state control
	const std::string _walkSignal[4] = {"walkW", "walkA", "walkS", "walkD"};
	const std::string _runSignal[4] = {"runW", "runA", "runS", "runD"};;
	int walkW;
	int walkA;
	int walkS;
	int walkD;
	int runW;
	int runA;
	int runS;
	int runD;
	int standW;
	int standA;
	int standS;
	int standD;
};

#endif
