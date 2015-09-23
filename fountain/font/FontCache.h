#if !defined(_FEI_FONTCACHE_H_)
#define _FEI_FONTCACHE_H_

#include "base/basedef.h"
#include "render/Texture.h"
#include "font/Font.h"

namespace fei
{

class FontCache
{
public:
	FontCache();
	~FontCache();

	void loadFont(const char* fontFile);
	void unloadFont();
	void updateCache(const std::vector<unsigned long>& str);
	void deleteCache();

	const Image queryCharactor();
	int queryKerning();

private:
	Texture cacheTexture;

	FT_Face face;

	bool isLoadedFont;
	FT_Bool useKerning;
};

}

#endif
