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
	charClock.init();

	Circle circle(10.0f);

	body = Physics::getInstance()->createBody(Vec2::ZERO);
	body->createFixture(&circle);
}

void Charactor::destroy()
{
	Physics::getInstance()->destroyBody(body);
}

void Charactor::drawIt()
{
	if (curAnime) {
		curAnime->draw();
	}
}

void Charactor::update()
{
	charClock.tick();
	setPosition(body->getPosition());
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
	body->setSpeed(speed);
	int ri = v.getQuadrantIndex();
	v.rotate(-45.0f);
	int i = v.getQuadrantIndex();
	if (sp < 150) curAnime = &walkAnime[i];
	else curAnime = &runAnime[ri];
}
