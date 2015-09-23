#include "Font.h"

using fei::Font;

Font* Font::instance = nullptr;

Font* Font::getInstance()
{
	if (!instance) {
		instance = new Font;
	}
	return instance;
}

bool Font::init()
{
	int error = FT_Init_FreeType(&library);
	if (error) {
		return false;
	}
	int major, minor, patch;
	FT_Library_Version(library, &major, &minor, &patch);
	std::printf("FreeType Version: %d.%d.%d\n", major, minor, patch);
	return true;
}

void Font::destroy()
{
	FT_Done_FreeType(library);	
}
