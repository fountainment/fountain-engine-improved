#include "FrameAnime.h"

using fei::FrameAnime;

FrameAnime::FrameAnime()
: curFrameIndex(0),
  fps(60.0f)
{
}

void FrameAnime::load(const fei::ImagePool& imagePool)
{
	framePool = imagePool;
	curFrameIndex = 0;
}

void FrameAnime::load(const fei::Texture& texture, const char* sipName)
{
	framePool.load(texture, sipName);
	setHasAlpha(texture.hasAlpha());
	curFrameIndex = 0;
}

void FrameAnime::load(const char* textureName, const char* sipName)
{
	fei::Texture tmpTex;
	tmpTex.load(textureName);
	load(tmpTex, sipName);
}

void FrameAnime::update()
{
	playClock.tick();
	if (playClock.isPlay()) {
		curFrameIndex += getFps() * playClock.getDeltaTime();
		if (curFrameIndex >= getFrameNum()) {
			if (isLoop()) {
				curFrameIndex = 0;
			} else {
				playClock.stop();
			}
		}
	}
}

void FrameAnime::drawIt()
{
	if (!playClock.isStop()) {
		fei::Image *image = framePool.getImage((int)curFrameIndex);
		if (image) {
			image->draw();
		}
	}
}

float FrameAnime::getFps()
{
	return fps;
}

void FrameAnime::setFps(float f)
{
	fps = f;
}

int FrameAnime::getFrameNum()
{
	return framePool.getImageNum();
}

int FrameAnime::getCurFrameIndex()
{
	return (int)curFrameIndex;
}

void FrameAnime::setCurFrameIndex(int cfi)
{
	curFrameIndex = cfi;
}
