#include "fountain.h"
#include "Charactor.h"

using namespace fei;

Charactor::Charactor()
: curAnime(nullptr)
{
}

void Charactor::init()
{
	walkAnime[0].load("res/image/Walk_B.png", "res/image/Walk_B.sip");
	walkAnime[1].load("res/image/Walk_L.png", "res/image/Walk_L.sip");
	walkAnime[2].load("res/image/Walk_F.png", "res/image/Walk_F.sip");
	walkAnime[3].load("res/image/Walk_R.png", "res/image/Walk_R.sip");
	runAnime[0].load("res/image/Run_B.png", "res/image/Run_B.sip");
	runAnime[1].load("res/image/Run_B.png", "res/image/Run_B.sip");
	runAnime[2].load("res/image/Run_F.png", "res/image/Run_F.sip");
	runAnime[3].load("res/image/Run_F.png", "res/image/Run_F.sip");
	for (int i = 0; i < 4; i++) {
		walkAnime[i].setLoop(true);
		walkAnime[i].setFps(15);
		runAnime[i].setLoop(true);
		runAnime[i].setFps(15);
	}
	curAnime = &walkAnime[0];
	poly.setSolid(false);
	poly.pushPoint(Vec2(-100.0f));
	poly.pushPoint(Vec2(100.0f, -100.0f));
	poly.pushPoint(Vec2(100.0f));
	poly.pushPoint(Vec2(-100.0f, 100.0f));
	poly1.pushPoint(Vec2(-100.0f));
	poly1.pushPoint(Vec2(0.0f, -100.0f));
	poly1.pushPoint(Vec2(-50.0f, 0.0f));
	poly2.pushPoint(Vec2(-90.0f, 30.0f));
	poly2.pushPoint(Vec2(-60.0f, 30.0f));
	poly2.pushPoint(Vec2(-75.0f, 35.0f));
	poly3.pushPoint(Vec2(-40.0f, 30.0f));
	poly3.pushPoint(Vec2(-10.0f, 30.0f));
	poly3.pushPoint(Vec2(-25.0f, 35.0f));
	charClock.init();
}

void Charactor::drawIt()
{
	Render::getInstance()->drawShape(&poly);
	Render::getInstance()->drawShape(&poly1);
	Render::getInstance()->drawShape(&poly2);
	Render::getInstance()->drawShape(&poly3);
	if (curAnime) {
		curAnime->draw();
	}
}

void Charactor::update()
{
	charClock.tick();
	move(speed * (float)charClock.getDeltaTime());
	if (curAnime) {
		curAnime->update();
	}
}

void Charactor::setSpeed(const Vec2& sp)
{
	speed = sp;
}

void Charactor::setSpeed(const fei::Vec2& drct, float sp)
{
	auto v = drct.normalized();
	speed = v * sp;
	int ri = v.getQuadrantIndex();
	v.rotate(-45.0f);
	int i = v.getQuadrantIndex();
	if (sp < 150) curAnime = &walkAnime[i];
	else curAnime = &runAnime[ri];
}
