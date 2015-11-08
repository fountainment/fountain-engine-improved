#if !defined(_BOMBER_H_)
#define _BOMBER_H_

#include "fountain.h"

//TODO: test a bomber on the map

class Bomber : public fei::RenderObj
{
public:
	Charactor();

	virtual void drawIt() override;
	virtual void init() override;
	virtual void destroy() override;
	virtual void update() override;

	void setSpeed(const fei::Vec2& sp);
	void setSpeed(const fei::Vec2& drct, float sp);

	void die();

	fei::Clock charClock;

private:
	fei::Vec2 speed;
	fei::Body *body;

	fei::FrameAnime *curAnime;
};

#endif
