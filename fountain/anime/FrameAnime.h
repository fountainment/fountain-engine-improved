#ifndef _FEI_FRAMEANIME_H_
#define _FEI_FRAMEANIME_H_

#include "anime/Anime.h"
#include "base/basedef.h"
#include "render/ImagePool.h"
#include "render/RenderObj.h"
#include "render/Texture.h"

namespace fei {

class FrameAnime : public Anime
{
public:
	FrameAnime();

	void load(const ImagePool& imagePool);
	void load(const std::string& name);
	void load(const std::string& name1, const std::string& name2);
	void loadTextureAndSIP(const Texture& texture, const std::string& sipName);
	void loadImageFileAndSIP(const std::string& name);
	void loadImageFileAndSIP(const std::string& textureName, const std::string& sipName);
	void loadTextureAndIPI(const Texture& texture, const std::string& ipiName);
	void loadImageFileAndIPI(const std::string& name);
	void loadImageFileAndIPI(const std::string& textureName, const std::string& ipiName);
	void loadImagePool(ImagePool imagePool);

	virtual void feiObjectUpdate(RenderObj* rObj) override;
	void updateFrameIndex();
	virtual void updateFrameContent(RenderObj* rObj);

	float getFps();
	void setFps(float f);

	int getFrameNum();
	int getCurFrameIndex();
	void setCurFrameIndex(int cfi);

	ImagePool* getFramePool();

	float getTotalTime();

protected:
	virtual void afterStop() override;

private:
	double _curFrameIndex;
	float _fps;
	ImagePool _framePool;
};

} // namespace fei

#endif // _FEI_FRAMEANIME_H_
