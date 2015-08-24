#include "FrameAnime.h"

using fei::FrameAnime;

FrameAnime::FrameAnime()
: curFrameIndex(0),
  fps(60.0f)
{
}

void FrameAnime::load(const ImagePool& imagePool)
{
	framePool = imagePool;
	curFrameIndex = 0;
}

void FrameAnime::load(const Texture& texture, const char* sipName)
{
	framePool.load(texture, sipName);
	curFrameIndex = 0;
}

void FrameAnime::load(const char* textureName, const char* sipName)
{
	framePool.load(textureName, sipName);
	curFrameIndex = 0;
}

void FrameAnime::update()
{
	tick();
	if (isPlay()) {
		curFrameIndex += getFps() * getDeltaTime();
		if (curFrameIndex >= getFrameNum()) {
			if (isLoop()) {
				curFrameIndex = 0;
			} else {
				stop();
			}
		}
	}
}

void FrameAnime::drawIt()
{
	if (!isStop()) {
		fei::Image *image = framePool.getImage(curFrameIndex);
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
	return curFrameIndex;
}

void FrameAnime::setCurFrameIndex(int cfi)
{
	curFrameIndex = cfi;
}