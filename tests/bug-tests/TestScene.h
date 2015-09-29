#if !defined(_TESTSCENE_H_)
#define _TESTSCENE_H_

#include "fountain.h"

class TestScene : public fei::Scene
{
public:
	void init() override;
	void destroy() override;
	void update() override;

	void keyCallback(int key, int scancode, int action, int mods) override;
	void scrollCallback(double xoffset, double yoffset) override;

private:
	void testMath();
	void testPhysics();
	void testRender();
	void testAudio();
	void testFont();

	fei::Texture testTex;
	fei::Source src;
	fei::Camera mainCam;
	fei::FontCache fc;
};

#endif
