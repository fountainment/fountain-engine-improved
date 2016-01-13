#if !defined(_TESTSCENE_H_)
#define _TESTSCENE_H_

#include "fountain.h"

class MyButton : public fei::Button
{
public:
	void init() override
	{
		setRectSize(fei::Vec2(100.0f, 40.0f));
		getLabel()->setCenterAligned(true);
		getLabel()->setPosition((getRectSize() - fei::Vec2(0.0f, 16.0f)) / 2.0f);
	}

private:
	void onEnter() override
	{
		setBackColor(fei::Color::Orange);
		setFrontColor(fei::Color::White);
	}

	void onLeave() override
	{
		setBackColor(fei::Color::White);
		setFrontColor(fei::Color::Black);
	}
};

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
	fei::Label label;
	MyButton button;
	fei::Image emptyImage;
};

#endif
