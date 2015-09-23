#if !defined(_FEI_FONTCACHE_H_)
#define _FEI_FONTCACHE_H_

#include "base/basedef.h"
#include "render/Texture.h"

namespace fei
{

class FontCache
{
public:
	void loadFont();
	void updateCache(const std::vector<unsigned long>& str);
	void deleteCache();

	const Image queryCharactor();

private:
	Texture cacheTexture;
	//FT_Face face;
};

}

#endif
