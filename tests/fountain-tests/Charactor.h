#if !defined(_CHARACTOR_H_)
#define _CHARACTOR_H_

#include "fountain.h"

class Charactor : public fei::RenderObj
{
public:
	Charactor();

	virtual void drawIt() override;
	virtual void init() override;
	virtual void update() override;

	void setSpeed(const fei::Vec2& sp);
	void setSpeed(const fei::Vec2& drct, float sp);

	fei::Clock charClock;

private:
	fei::Vec2 speed;

	fei::FrameAnime *curAnime;
	fei::FrameAnime walkAnime[4];
	fei::FrameAnime runAnime[4];

	//TODO: anime state control
};

#endif
