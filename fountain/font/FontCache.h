#if !defined(_FEI_FONTCACHE_H_)
#define _FEI_FONTCACHE_H_

//TODO: add bold function

#include "base/basedef.h"
#include "font/Font.h"
#include "render/Texture.h"

namespace fei
{

class FontCache
{
public:
	FontCache();
	~FontCache();

	void loadFont(const std::string& fontFile, int fontSize = 16);
	void unloadFont();
	void updateCache(const std::vector<unsigned long>& str);
	void updateCache(const std::string& str);
	void deleteCache();

	int getRemainingSpace();

	const Image queryCharactor(unsigned long c);
	int queryKerning(unsigned long left, unsigned long right);
	int queryAdvance(unsigned long c);

	const Texture getCacheTexture();

private:
	void initCacheTexture();
	void updateCache(unsigned long* str, int strSize);

	Texture _cacheTexture;

	FT_Face _face;

	int _gridSize;
	int _gridNum;
	int _curRow;
	int _curCol;

	std::map<unsigned long, Image> _charImageMap;
	std::map<unsigned long, int> _charAdvanceMap;

	bool _fontIsLoaded;
	FT_Bool _useKerning;
};

} // namespace fei

#endif // _FEI_FONTCACHE_H_
