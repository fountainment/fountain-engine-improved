#include "FontCache.h"
#include "render/Image.h"

using fei::FontCache;

FontCache::FontCache()
: isLoadedFont(false),
  useKerning(false)
{
}

FontCache::~FontCache()
{
	deleteCache();
	unloadFont();
}

void FontCache::loadFont(const char* fontFile)
{
	if (!Font::getInstance()->isLoaded()) {
		std::fprintf(stderr, "FontCache: Font module not loaded!\n");
		return;
	}
	unloadFont();
	FT_Library *library = &Font::getInstance()->library;
	int error = FT_New_Face(*library, fontFile, 0, &face);
	if (error) {
		std::fprintf(stderr, "FontCache: \"%s\" loading error!\n", fontFile);
		return;
	}
	isLoadedFont = true;
	useKerning = FT_HAS_KERNING(face);
}

void FontCache::unloadFont()
{
	if (!isLoadedFont) {
		return;
	}
	isLoadedFont = false;
	useKerning = false;
	if (!Font::getInstance()->isLoaded()) {
		return;
	}
	FT_Done_Face(face);
}

void FontCache::updateCache(const std::vector<unsigned long>& str)
{
	if (!cacheTexture.isLoaded()) {
		cacheTexture.load(nullptr, 2048, 2048, fei::Texture::Format::LUMA);
	}
	for (auto charactor : str) {
		//TODO:
	}
}

void FontCache::deleteCache()
{
	cacheTexture.unload();
}

const fei::Image FontCache::queryCharactor()
{
	//TODO: implement queryCharactor
	return cacheTexture.getImage();
}
