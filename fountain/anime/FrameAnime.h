#if !defined(_FEI_FRAMEANIME_H_)
#define _FEI_FRAMEANIME_H_

#include "render/RenderObj.h"
#include "render/Texture.h"
#include "render/ImagePool.h"
#include "anime/Anime.h"
#include "base/basedef.h"

namespace fei {

class FrameAnime : public Anime
{
public:
	FrameAnime();

	void load(const ImagePool& imagePool);
	void load(const Texture& texture, const std::string& sipName);
	void load(const std::string& textureName, const std::string& sipName);

	virtual void update(RenderObj* rObj) override;

	float getFps();
	void setFps(float f);

	int getFrameNum();
	int getCurFrameIndex();
	void setCurFrameIndex(int cfi);

private:
	double curFrameIndex;
	float fps;
	ImagePool framePool;
};

}

#endif
