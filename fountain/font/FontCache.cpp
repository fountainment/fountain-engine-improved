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
	gridSize = fontSize + (fontSize & 1);
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
	//TODO: optimize updateCache speed
	assert(isLoadedFont);
	if (!cacheTexture.isLoaded()) {
		int maxTextureSize = Render::getInstance()->getMaxTextureSize();
		int texSize = std::min(4096, maxTextureSize);
		gridNum = texSize / gridSize;
		curRow = 0;
		curCol = 0;
		cacheTexture.load(nullptr, texSize, texSize, fei::Texture::Format::LUMA);
	}
	FT_GlyphSlot slot = face->glyph;
	auto bits = new unsigned char[gridSize * gridSize * 2];
	for (auto charactor : str) {
		if (curRow >= gridNum) {
			std::fprintf(stderr, "FontCache: Overflow!\n");
			break;
		}
		FT_Load_Char(face, charactor, FT_LOAD_RENDER);
		FT_Bitmap& bitmap = slot->bitmap;
		int width = (int)bitmap.width;
		int rows = (int)bitmap.rows;
		int &cols = gridSize;
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				int bitsIndex = row * cols + col;
				unsigned char bufferBit = (col < width) ? bitmap.buffer[(rows - row - 1) * width + col] : 0;
				bits[(bitsIndex << 1)] = 255;
				bits[(bitsIndex << 1) + 1] = bufferBit;
			}
		}
		cacheTexture.subUpdate(bits, cols, rows, fei::Texture::Format::LUMA, curCol * gridSize, curRow * gridSize);
		if (++curCol >= gridNum) {
			curCol = 0;
			curRow++;
		}
	}
	delete [] bits;
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
