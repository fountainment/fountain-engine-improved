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

	fei::Clock charClock;

private:
	fei::FrameAnime *curAnime;
	fei::FrameAnime anime;
	//TODO: anime state control
};

#endif
