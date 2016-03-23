#include "anime/FrameAnime.h"

using fei::FrameAnime;

FrameAnime::FrameAnime()
: _curFrameIndex(0),
  _fps(60.0f)
{
}

void FrameAnime::load(const fei::ImagePool& imagePool)
{
	_framePool = imagePool;
	_curFrameIndex = 0;
}

void FrameAnime::loadTextureAndSIP(const fei::Texture& texture, const std::string& sipName)
{
	_framePool.loadTextureAndSIP(texture, sipName);
	_curFrameIndex = 0;
}

void FrameAnime::load(const std::string& name)
{
	loadImageFileAndSIP(name);
}

void FrameAnime::load(const std::string& name1, const std::string& name2)
{
	loadImageFileAndSIP(name1, name2);
}

void FrameAnime::loadImageFileAndSIP(const std::string& name)
{
	loadImageFileAndSIP(name + ".png", name + ".sip");
}

void FrameAnime::loadImageFileAndSIP(const std::string& textureName, const std::string& sipName)
{
	fei::Texture tmpTex;
	tmpTex.load(textureName);
	loadTextureAndSIP(tmpTex, sipName);
}

void FrameAnime::loadImageFileAndIPI(const std::string& name)
{
	loadImageFileAndIPI(name + ".png", name + ".ipi");
}

void FrameAnime::loadImageFileAndIPI(const std::string& textureName, const std::string& ipiName)
{
	fei::Texture tmpTex;
	tmpTex.load(textureName);
	loadTextureAndIPI(tmpTex, ipiName);
}

void FrameAnime::loadTextureAndIPI(const fei::Texture& texture, const std::string& ipiName)
{
	_framePool.loadTextureAndIPI(texture, ipiName);
	_curFrameIndex = 0;
}

void FrameAnime::feiObjectUpdate(fei::RenderObj* rObj)
{
	updateFrameIndex();
	updateFrameContent(rObj);
	update(rObj);
}

void FrameAnime::updateFrameIndex()
{
	if (isPlay()) {
		_curFrameIndex += getFps() * getDeltaTime();
		if (_curFrameIndex >= getFrameNum()) {
			_curFrameIndex = 0;
			if (!isLoop()) {
				stop();
			}
		}
	}
}

void FrameAnime::updateFrameContent(fei::RenderObj* rObj)
{
	//not set null when stop
	//rObj->setSubstitute(nullptr);
	if (!isStop()) {
		fei::Image *image = _framePool.getImage((int)_curFrameIndex);
		rObj->setSubstitute(image);
	}
}

float FrameAnime::getFps()
{
	return _fps;
}

void FrameAnime::setFps(float f)
{
	_fps = f;
}

int FrameAnime::getFrameNum()
{
	return _framePool.getImageNum();
}

int FrameAnime::getCurFrameIndex()
{
	return (int)_curFrameIndex;
}

void FrameAnime::setCurFrameIndex(int cfi)
{
	_curFrameIndex = cfi;
}

fei::ImagePool* FrameAnime::getFramePool()
{
	return &_framePool;
}
