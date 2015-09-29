#include "FontCache.h"
#include "render/Image.h"

using fei::FontCache;

FontCache::FontCache()
: gridSize(0),
  gridNum(0),
  curRow(0),
  curCol(0),
  isLoadedFont(false),
  useKerning(false)
{
	cacheTexture.setIsAlpha(true);
}

FontCache::~FontCache()
{
	deleteCache();
	unloadFont();
}

void FontCache::loadFont(const char* fontFile, int fontSize)
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
	FT_Set_Pixel_Sizes(face, 0, fontSize);
	gridSize = fontSize + (fontSize & 1) + 2;
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

void FontCache::updateCache(unsigned long* str, int strSize)
{
	assert(strSize > 0 && cacheTexture.isLoaded());
	int gridW = std::min(strSize, gridNum);
	int gridH = strSize / gridNum;
	if (!gridH) {
		gridH = 1;
	}
	int bitsW = gridW * gridSize;
	int bitsH = gridH * gridSize;
	int xLoc = curCol * gridSize;
	int yLoc = curRow * gridSize;

	FT_GlyphSlot slot = face->glyph;

	auto bits = new unsigned char[bitsW * bitsH * 2];
	for (int i = 0; i < strSize; i++) {
		int gridX = i % gridW;
		int gridY = i / gridW;
		FT_Load_Char(face, str[i], FT_LOAD_RENDER);
		FT_Bitmap& bitmap = slot->bitmap;
		int bitW = (int)bitmap.width;
		int bitH = (int)bitmap.rows;
		int lbX = gridX * gridSize;
		int lbY = gridY * gridSize;
		for (int bitY = 0; bitY < gridSize; bitY++) {
			for (int bitX = 0; bitX < gridSize; bitX++) {
				int bitsX = lbX + bitX;
				int bitsY = lbY + bitY;
				int bitsIndex = bitsY * bitsW * 2 + bitsX * 2;
				bits[bitsIndex] = 255;
				bits[bitsIndex + 1] = (bitX >= 1 && bitX <= bitW && bitY >= 1 && bitY <= bitH)?
					bitmap.buffer[(bitH - bitY) * bitW + bitX - 1]:0;
			}
		}
		fei::Image image = cacheTexture.getImage(fei::Rect(lbX + 1, lbY + 1, bitW, bitH));
		fei::Vec2 anchor(slot->bitmap_left + bitmap.width / 2.0f, slot->bitmap_top - bitmap.rows / 2.0f);
		anchor *= -1.0f;
		image.setAnchor(anchor);
		//TODO: Store the image
	}
	cacheTexture.subUpdate(bits, bitsW, bitsH, fei::Texture::Format::LUMA, xLoc, yLoc);
	delete bits;
	curCol += strSize;
	curRow += curCol / gridNum;
	curCol %= gridNum;
}

void FontCache::updateCache(const std::vector<unsigned long>& str)
{
	assert(isLoadedFont);
	if (!cacheTexture.isLoaded()) {
		int maxTextureSize = Render::getInstance()->getMaxTextureSize();
		int texSize = std::min(4096, maxTextureSize);
		gridNum = texSize / gridSize;
		curRow = 0;
		curCol = 0;
		cacheTexture.load(nullptr, texSize, texSize, fei::Texture::Format::LUMA);
	}
	auto strCopy = str;
	std::sort(strCopy.begin(), strCopy.end());
	strCopy.erase(std::unique(strCopy.begin(), strCopy.end()), strCopy.end());
	int updateSize = strCopy.size();
	int strIndex = 0;
	while (updateSize) {
		int subUpdateSize;
		if (curCol != 0) {
			subUpdateSize = std::min(updateSize, gridNum - curCol);
		} else {
			int wholeLine = updateSize / gridNum;
			if (!wholeLine) {
				subUpdateSize = updateSize;
			} else {
				subUpdateSize = wholeLine * gridNum;
			}
		}
		updateCache(&strCopy[strIndex], subUpdateSize);
		strIndex += subUpdateSize;
		updateSize -= subUpdateSize;
	}
}

void FontCache::deleteCache()
{
	cacheTexture.unload();
}

const fei::Image FontCache::queryCharactor(unsigned long c)
{
	//TODO: implement queryCharactor
	return cacheTexture.getImage();
}

int FontCache::queryKerning(unsigned long left, unsigned long right)
{
	if (!useKerning) {
		return 0;
	}
	FT_Vector delta;
	FT_UInt leftIndex, rightIndex;
	leftIndex = FT_Get_Char_Index(face, left);
	rightIndex = FT_Get_Char_Index(face, right);
	FT_Get_Kerning(face, leftIndex, rightIndex, FT_KERNING_DEFAULT, &delta);
	return delta.x >> 6;
}

const fei::Texture FontCache::getCacheTexture()
{
	return cacheTexture;
}
