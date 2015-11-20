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

	Rect rect(Vec2(40, 20));
	rect.setCenter(Vec2(0, -20));

	body = Physics::getInstance()->createBody(Vec2::ZERO);
	auto b2bd = body->getB2Body();
	b2bd->SetFixedRotation(true);
	b2bd->SetGravityScale(0.0f);
	body->createFixture(&rect);

	atk1Anime.setFps(15);
	atk1Anime.load("res/image/CA_B01_B");
	atk1Anime.setBody(body);
	atk1Anime.loadCollisionFile("res/colli/CA01B.col");

	atk2Anime.setFps(15);
	atk2Anime.load("res/image/CA_B02_B");
	atk2Anime.setBody(body);
	atk2Anime.loadCollisionFile("res/colli/CA02B.col");

	atk3Anime.setFps(15);
	atk3Anime.load("res/image/CA_B03_B");
	atk3Anime.setBody(body);
	atk3Anime.loadCollisionFile("res/colli/CA03B.col");
}

void Charactor::destroy()
{
	Physics::getInstance()->destroyBody(body);
}

void Charactor::drawIt()
{
}

void Charactor::update()
{
	setPosition(body->getPosition());
	if (curAnime && curAnime->isStop()) {
		curAnime = &walkAnime[0];
	}
	setAnime(curAnime);
}

void Charactor::setSpeed(const Vec2& sp)
{
	speed = sp;
	body->setSpeed(speed);
}

void Charactor::setSpeed(const fei::Vec2& drct, float sp)
{
	auto v = drct.normalized();
	speed = v * sp;
	body->setSpeed(speed);
	int ri = v.getQuadrantIndex();
	v.rotate(-45.0f);
	int i = v.getQuadrantIndex();
	if (speed.getLength() < 1.0f) return; 
	if (sp < 150) curAnime = &walkAnime[i];
	else curAnime = &runAnime[ri];
}

void Charactor::attack()
{
	if (curAnime == &atk1Anime) {
		atk1Anime.destroyFixture();
		curAnime = &atk2Anime;
	} else if (curAnime == &atk2Anime) {
		atk2Anime.destroyFixture();
		curAnime = &atk3Anime;
	} else if (curAnime == &atk3Anime) {
		return;
	} else {
		curAnime = &atk1Anime;
	}
	curAnime->stop();
	curAnime->play();
	curAnime->setCurFrameIndex(0);
}
