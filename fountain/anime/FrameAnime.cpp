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

void FrameAnime::load(const fei::Texture& texture, const std::string& sipName)
{
	framePool.load(texture, sipName);
	curFrameIndex = 0;
}

void FrameAnime::load(const std::string& textureName, const std::string& sipName)
{
	fei::Texture tmpTex;
	tmpTex.load(textureName);
	load(tmpTex, sipName);
}

void FrameAnime::feiUpdate(fei::RenderObj* rObj)
{
	updateFrameIndex();
	updateFrameContent(rObj);
	update(rObj);
}

void FrameAnime::updateFrameIndex()
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

void FrameAnime::updateFrameContent(fei::RenderObj* rObj)
{
	rObj->setSubstitute(nullptr);
	if (!playClock.isStop()) {
		fei::Image *image = framePool.getImage((int)curFrameIndex);
		rObj->setSubstitute(image);
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
