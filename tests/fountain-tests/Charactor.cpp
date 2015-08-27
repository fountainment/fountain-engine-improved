#include "fountain.h"
#include "Charactor.h"

using namespace fei;

Charactor::Charactor()
: curAnime(nullptr)
{
}

void Charactor::init()
{
}

void Charactor::drawIt()
{
	if (curAnime) {
		curAnime->draw();
	}
}

void Charactor::update()
{
	if (curAnime) {
		curAnime->update();
	}
}

