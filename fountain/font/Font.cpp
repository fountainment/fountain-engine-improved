#include "font/Font.h"

using fei::Font;

Font* Font::instance_ = nullptr;

Font* Font::getInstance()
{
	if (!instance_) {
		instance_ = new Font;
	}
	return instance_;
}

bool Font::init()
{
	int error = FT_Init_FreeType(&_library);
	if (error) {
		return false;
	}
	int major, minor, patch;
	FT_Library_Version(_library, &major, &minor, &patch);
	std::printf("FreeType Version: %d.%d.%d\n", major, minor, patch);
	return true;
}

void Font::destroy()
{
	FT_Done_FreeType(_library);
}
