#include "font/FontCache.h"

#include "math/coding.h"
#include "render/Image.h"

using fei::FontCache;

FontCache::FontCache()
: _gridSize(0),
  _gridNum(0),
  _curRow(0),
  _curCol(0),
  _fontIsLoaded(false),
  _useKerning(false)
{
	_cacheTexture.setHasAlpha(true);
}

FontCache::~FontCache()
{
	deleteCache();
	unloadFont();
}

void FontCache::loadFont(const std::string& fontFile, int fontSize)
{
	if (!Font::getInstance()->isLoaded()) {
		std::fprintf(stderr, "FontCache: Font module not loaded!\n");
		return;
	}
	unloadFont();
	FT_Library *library = &Font::getInstance()->library;
	int error = FT_New_Face(*library, fontFile.c_str(), 0, &_face);
	if (error) {
		std::fprintf(stderr, "FontCache: \"%s\" loading error!\n", fontFile.c_str());
		return;
	}
	_fontIsLoaded = true;
	FT_Set_Pixel_Sizes(_face, 0, fontSize);
	_gridSize = fontSize + (fontSize & 1) + 2;
	_useKerning = FT_HAS_KERNING(_face);
}

void FontCache::unloadFont()
{
	if (!_fontIsLoaded) {
		return;
	}
	_fontIsLoaded= false;
	_useKerning = false;
	if (!Font::getInstance()->isLoaded()) {
		return;
	}
	FT_Done_Face(_face);
}

void FontCache::updateCache(unsigned long* str, int strSize)
{
	assert(strSize > 0 && _cacheTexture.isLoaded());
	int gridW = std::min(strSize, _gridNum);
	int gridH = strSize / _gridNum;
	if (!gridH) {
		gridH = 1;
	}
	int bitsW = gridW * _gridSize;
	int bitsH = gridH * _gridSize;
	int xLoc = _curCol * _gridSize;
	int yLoc = _curRow * _gridSize;

	FT_Error error;
	FT_GlyphSlot slot = _face->glyph;

	auto bits = new unsigned char[bitsW * bitsH * 2];
	for (int i = 0; i < strSize; i++) {
		int gridX = i % gridW;
		int gridY = i / gridW;
		error = FT_Load_Char(_face, str[i], FT_LOAD_RENDER);
		if (error) {
			continue;
		}
		FT_Bitmap& bitmap = slot->bitmap;
		int bitW = (int)bitmap.width;
		int bitH = (int)bitmap.rows;
		int lbX = gridX * _gridSize;
		int lbY = gridY * _gridSize;
		for (int bitY = 0; bitY < _gridSize; bitY++) {
			for (int bitX = 0; bitX < _gridSize; bitX++) {
				int bitsX = lbX + bitX;
				int bitsY = lbY + bitY;
				int bitsIndex = bitsY * bitsW * 2 + bitsX * 2;
				bits[bitsIndex] = 255;
				bits[bitsIndex + 1] = (bitX >= 1 && bitX <= bitW && bitY >= 1 && bitY <= bitH)?
					bitmap.buffer[(bitH - bitY) * bitW + bitX - 1]:0;
			}
		}
		fei::Image image = _cacheTexture.getImage(fei::Rect((float)xLoc + lbX + 1, (float)yLoc + lbY + 1, (float)bitW, (float)bitH));
		fei::Vec2 anchor(slot->bitmap_left + bitmap.width / 2.0f, slot->bitmap_top - bitmap.rows / 2.0f);
		anchor *= -1.0f;
		image.setAnchor(anchor);
		_charImageMap[str[i]] = image;
		_charAdvanceMap[str[i]] = slot->advance.x >> 6;
	}
	_cacheTexture.subUpdate(bits, bitsW, bitsH, fei::Texture::Format::LUMA, xLoc, yLoc);
	delete bits;
	_curCol += strSize;
	_curRow += _curCol / _gridNum;
	_curCol %= _gridNum;
}

void FontCache::initCacheTexture()
{
	int maxTextureSize = Render::getInstance()->getMaxTextureSize();
	int texSize = std::min(4096, maxTextureSize);
	_gridNum = texSize / _gridSize;
	_curRow = 0;
	_curCol = 0;
	_cacheTexture.load(nullptr, texSize, texSize, fei::Texture::Format::LUMA);
}

void FontCache::updateCache(const std::vector<unsigned long>& str)
{
	if (!_fontIsLoaded) {
		return;
	}
	if (!_cacheTexture.isLoaded()) {
		initCacheTexture();
	}
	auto strCopy = str;
	std::sort(strCopy.begin(), strCopy.end());
	strCopy.erase(std::unique(strCopy.begin(), strCopy.end()), strCopy.end());
	int updateSize = strCopy.size();
	int strIndex = 0;
	int remainingSpace = getRemainingSpace();
	if (updateSize > remainingSpace) {
		int dissmissed = updateSize - remainingSpace;
		updateSize = remainingSpace;
		std::fprintf(stderr, "FontCache: Cache overflow! (%d charactors dismissed)\n", dissmissed);
	}
	while (updateSize > 0) {
		int subUpdateSize;
		if (_curCol != 0) {
			subUpdateSize = std::min(updateSize, _gridNum - _curCol);
		} else {
			int wholeLine = updateSize / _gridNum;
			if (!wholeLine) {
				subUpdateSize = updateSize;
			} else {
				subUpdateSize = wholeLine * _gridNum;
			}
		}
		updateCache(&strCopy[strIndex], subUpdateSize);
		strIndex += subUpdateSize;
		updateSize -= subUpdateSize;
	}
}

void FontCache::updateCache(const std::string& str)
{
	updateCache(fei::utf8ToUnicode(str));
}

void FontCache::deleteCache()
{
	_cacheTexture.unload();
}

int FontCache::getRemainingSpace()
{
	if (!_fontIsLoaded) {
		return 0;
	}
	return (_gridNum - _curRow - 1) * _gridNum + (_gridNum - _curCol);
}

const fei::Image FontCache::queryCharactor(unsigned long c)
{
	auto it = _charImageMap.find(c);
	if (it == _charImageMap.end()) {
		std::vector<unsigned long> tmp;
		tmp.push_back(c);
		updateCache(tmp);
		it = _charImageMap.find(c);
	}
	return it->second;
}

int FontCache::queryKerning(unsigned long left, unsigned long right)
{
	if (!_useKerning) {
		return 0;
	}
	FT_Vector delta;
	FT_UInt leftIndex, rightIndex;
	leftIndex = FT_Get_Char_Index(_face, left);
	rightIndex = FT_Get_Char_Index(_face, right);
	FT_Get_Kerning(_face, leftIndex, rightIndex, FT_KERNING_DEFAULT, &delta);
	return delta.x >> 6;
}

int FontCache::queryAdvance(unsigned long c)
{
	auto it = _charAdvanceMap.find(c);
	if (it == _charAdvanceMap.end()) {
		updateCache(&c, 1);
		it = _charAdvanceMap.find(c);
	}
	return it->second;
}

const fei::Texture FontCache::getCacheTexture()
{
	return _cacheTexture;
}
