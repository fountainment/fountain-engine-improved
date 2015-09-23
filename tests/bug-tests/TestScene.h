#if !defined(_TESTSCENE_H_)
#define _TESTSCENE_H_

#include "fountain.h"

class TestScene : public fei::Scene
{
public:
	void init() override;
	void destroy() override;
	void update() override;

private:
	void testMath();
	void testPhysics();
	void testRender();
	void testAudio();
	void testFont();
};

#endif
