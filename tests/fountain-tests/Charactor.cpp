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
	walkAnime[1].load("res/image/Walk_F.png", "res/image/Walk_F.sip");
	walkAnime[2].load("res/image/Walk_L.png", "res/image/Walk_L.sip");
	walkAnime[3].load("res/image/Walk_R.png", "res/image/Walk_R.sip");
	for (int i = 0; i < 4; i++) {
		walkAnime[i].setLoop(true);
		walkAnime[i].setFps(15);
	}
	curAnime = &walkAnime[0];
	charClock.init();
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
	move(speed * charClock.getDeltaTime());
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
}
