#include "fountain.h"
#include "Charactor.h"

using namespace fei;

const std::vector<std::string> Charactor::_walkSignal = {"walkW", "walkA", "walkS", "walkD"};
const std::vector<std::string> Charactor::_runSignal = {"runW", "runA", "runS", "runD"};

#define FPS 20

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
	CA1W = getStateId("CA1W");
	CA2W = getStateId("CA2W");
	CA3W = getStateId("CA3W");
	CA3Wx1 = getStateId("CA3Wx1");
	CA1S = getStateId("CA1S");
	CA2S = getStateId("CA2S");
	CA3Sx1 = getStateId("CA3Sx1");
	CA3S = getStateId("CA3S");
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
		walkAnime[i].setFps(FPS);
		runAnime[i].setLoop(true);
		runAnime[i].setFps(FPS);
		standAnime[i].setLoop(true);
		standAnime[i].setFps(FPS);
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

	atk1Anime.setFps(FPS);
	atk1Anime.loadImageFileAndIPI("res/image/Latte_longS_attack-1_B");
	atk1Anime.setBody(body);
	atk1Anime.loadCollisionFile("res/colli/CA01B.col");

	atk2Anime.setFps(FPS);
	atk2Anime.loadImageFileAndIPI("res/image/Latte_longS_attack-2_B");
	atk2Anime.setBody(body);
	atk2Anime.loadCollisionFile("res/colli/CA02B.col");

	atk3Anime.setFps(FPS);
	atk3Anime.loadImageFileAndIPI("res/image/Latte_longS_attack-3_B");
	atk3Anime.setBody(body);
	atk3Anime.loadCollisionFile("res/colli/CA03B.col");

	atk1AnimeS.setFps(FPS);
	atk1AnimeS.loadImageFileAndIPI("res/image/Latte_longS_attack-1_F");
	atk2AnimeS.setFps(FPS);
	atk2AnimeS.loadImageFileAndIPI("res/image/Latte_longS_attack-2_F");
	atk3AnimeS.setFps(FPS);
	atk3AnimeS.loadImageFileAndIPI("res/image/Latte_longS_attack-3_F");
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
	if (curAnime->isStop()) {
		inputSignal("stopAnime");
		setAnime(curAnime);
		curAnime->updateFrameContent(this);
	}
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
}

void Charactor::outputSignal(int signal)
{
	std::printf("%s\n", getStateName().c_str());
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
			if (state == CA1W) {
				atk1Anime.play();
				curAnime = &atk1Anime;
				break;
			}
			if (state == CA2W) {
				atk2Anime.play();
				curAnime = &atk2Anime;
				break;
			}
			if (state == CA3Wx1) {
				atk3Anime.play();
				curAnime = &atk3Anime;
				break;
			}
			if (state == CA1S) {
				atk1AnimeS.play();
				curAnime = &atk1AnimeS;
				break;
			}
			if (state == CA2S) {
				atk2AnimeS.play();
				curAnime = &atk2AnimeS;
				break;
			}
			if (state == CA3Sx1) {
				atk3AnimeS.play();
				curAnime = &atk3AnimeS;
				break;
			}
		} while(0);
	}
}
