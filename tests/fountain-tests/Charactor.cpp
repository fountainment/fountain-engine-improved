#include "fountain.h"
#include "Charactor.h"

using namespace fei;

Charactor::Charactor()
: curAnime(nullptr)
{
}

void Charactor::init()
{
	load("res/fsm/test");
	setState("standW");
	walkW = getStateId("walkW");
	walkA = getStateId("walkA");
	walkS = getStateId("walkS");
	walkD = getStateId("walkD");
	runW = getStateId("runW");
	runA = getStateId("runA");
	runS = getStateId("runS");
	runD = getStateId("runD");
	standW = getStateId("standW");
	standA = getStateId("standA");
	standS = getStateId("standS");
	standD = getStateId("standD");
	walkAnime[0].loadImageFileAndIPI("res/image/Latte_N_walk_B");
	walkAnime[1].loadImageFileAndIPI("res/image/Latte_N_walk_L");
	walkAnime[2].loadImageFileAndIPI("res/image/Latte_N_walk_F");
	walkAnime[3].loadImageFileAndIPI("res/image/Latte_N_walk_R");
	runAnime[0].loadImageFileAndIPI("res/image/Latte_N_run_B");
	runAnime[1].loadImageFileAndIPI("res/image/Latte_N_run_B");
	runAnime[2].loadImageFileAndIPI("res/image/Latte_N_run_F");
	runAnime[3].loadImageFileAndIPI("res/image/Latte_N_run_F");
	standAnime[0].loadImageFileAndIPI("res/image/Latte_N_breath_B");
	standAnime[1].loadImageFileAndIPI("res/image/Latte_N_breath_L");
	standAnime[2].loadImageFileAndIPI("res/image/Latte_N_breath_F");
	standAnime[3].loadImageFileAndIPI("res/image/Latte_N_breath_R");
	for (int i = 0; i < 4; i++) {
		walkAnime[i].setLoop(true);
		walkAnime[i].setFps(15);
		runAnime[i].setLoop(true);
		runAnime[i].setFps(15);
		standAnime[i].setLoop(true);
		standAnime[i].setFps(15);
	}
	curAnime = &standAnime[0];
	charClock.init();

	Rect rect(Vec2(25, 10));
	rect.setCenter(Vec2(0, 0));

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
	setAnime(curAnime);
}

void Charactor::setSpeed(const fei::Vec2& drct, float sp)
{
	auto v = drct.normalized();
	speed = v * sp;
	body->setSpeed(speed);
	v.rotate(-45.0f);
	int i = v.getQuadrantIndex();
	if (sp < 1.0f) {
		inputSignal("stop");
	} else if (sp < 150) {
		inputSignal(_walkSignal[i]);
	} else {
		inputSignal(_runSignal[i]);
	}
}

void Charactor::attack()
{
	inputSignal("attack");
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
	curAnime->play();
	curAnime->setCurFrameIndex(0);
}

void Charactor::outputSignal(int signal)
{
	if (signal == ChangeSig) {
		int state = getState();
		do {
			if (state == walkW) {
				curAnime = &walkAnime[0];
				break;
			}
			if (state == walkA) {
				curAnime = &walkAnime[1];
				break;
			}
			if (state == walkS) {
				curAnime = &walkAnime[2];
				break;
			}
			if (state == walkD) {
				curAnime = &walkAnime[3];
				break;
			}
			if (state == runW) {
				curAnime = &runAnime[0];
				break;
			}
			if (state == runA) {
				curAnime = &runAnime[1];
				break;
			}
			if (state == runS) {
				curAnime = &runAnime[2];
				break;
			}
			if (state == runD) {
				curAnime = &runAnime[3];
				break;
			}
			if (state == standW) {
				curAnime = &standAnime[0];
				break;
			}
			if (state == standA) {
				curAnime = &standAnime[1];
				break;
			}
			if (state == standS) {
				curAnime = &standAnime[2];
				break;
			}
			if (state == standD) {
				curAnime = &standAnime[3];
				break;
			}
		} while(0);
	}
}
