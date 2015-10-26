#if !defined(_FEI_ANIME_H_)
#define _FEI_ANIME_H_

#include "time/PlayObj.h"
#include "render/RenderObj.h"
#include "render/ImagePool.h"
#include "render/Texture.h"
#include "base/basedef.h"

namespace fei {

class Anime : public PlayObj
{
public:
	virtual ~Anime();

	void feiUpdate(RenderObj* rObj);
	virtual void update(RenderObj* rObj);

	static Anime* createFrameAnime(float fps, const fei::ImagePool& animeImage);
	static Anime* createFrameAnime(float fps, const fei::Texture& texture, const std::string& sipName);
	static Anime* createFrameAnime(float fps, const std::string& textureName, const std::string& sipName);
	static Anime* createActionAnime();

private:
};

}

#endif
