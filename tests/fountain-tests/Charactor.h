#if !defined(_CHARACTOR_H_)
#define _CHARACTOR_H_

#include "fountain.h"
#include "util/PhysicsAnime.h"
#include "util/FSM.h"

class CharFSM : public fut::FSM
{
private:
	virtual void outputSignal(int signal) override
	{
		std::printf("output: %d %s\n", signal, getStateName(getState()).c_str());
	};
};

class Charactor : public fei::RenderObj, public CharFSM
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
	fut::CollisionFrameAnime atk1Anime, atk2Anime, atk3Anime;
	fut::CollisionFrameAnime atk1AnimeS, atk2AnimeS, atk3AnimeS;
	//TODO: anime state control
	static const std::vector<std::string> _walkSignal;
	static const std::vector<std::string> _runSignal;
	int walkW, walkA, walkS, walkD;
	int runW, runA, runS, runD;
	int standW, standA, standS, standD;
	int CA1W, CA2W, CA3Wx1, CA3W;
	int CA1S, CA2S, CA3Sx1, CA3S;
};

#endif
