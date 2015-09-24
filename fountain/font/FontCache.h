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

	void loadFont(const char* fontFile, int fontSize = 16);
	void unloadFont();
	void updateCache(const std::vector<unsigned long>& str);
	void deleteCache();

	const Image queryCharactor(unsigned long c);
	int queryKerning(unsigned long left, unsigned long right);

	const Texture getCacheTexture();

private:
	Texture cacheTexture;

	FT_Face face;

	int gridSize;
	int gridNum;
	int curRow;
	int curCol;

	bool isLoadedFont;
	FT_Bool useKerning;
};

}

#endif
