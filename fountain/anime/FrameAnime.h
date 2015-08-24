#if !defined(_FEI_FRAMEANIME_H_)
#define _FEI_FRAMEANIME_H_

#include "render/RenderObj.h"
#include "render/Texture.h"
#include "render/ImagePool.h"

namespace fei {

class FrameAnime : public RenderObj
{
public:
	FrameAnime();

	void load(const ImagePool& imagePool);
	void load(const Texture& texture, const char* sipName);
	void load(const char* textureName, const char* sipName);

	virtual void update() override;
	virtual void drawIt() override;

	float getFps();
	void setFps(float f);

	int getFrameNum();
	int getCurFrameIndex();
	void setCurFrameIndex(int cfi);

private:
	int curFrameIndex;
	float fps;
	ImagePool framePool;
};

}

#endif