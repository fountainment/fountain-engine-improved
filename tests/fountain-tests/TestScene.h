#if !defined(_TESTSCENE_H_)
#define _TESTSCENE_H_

#include "fountain.h"
#include "Charactor.h"

using namespace fei;

class TestScene : public Scene
{
public:
	void init() override;
	void update() override;
private:
	Clock mainClock;
	Camera mainCam, UICam;
	Charactor mainChar;
	Texture UI, map;
	Layer UILayer;
};

#endif
