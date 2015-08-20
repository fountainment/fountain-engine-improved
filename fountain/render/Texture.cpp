#include "Texture.h"
#include "base/basedef.h"
#include "base/fileUtil.h"
#include <FreeImage.h>

using fei::Texture;

static GLenum Format2GLFormat(Texture::Format format)
{
	static GLenum ToGLFormat[] = {0, GL_RGB, GL_RGBA, GL_BGR, GL_BGRA, GL_LUMINANCE, GL_LUMINANCE_ALPHA};
	return ToGLFormat[(int)format];
}

static Texture::Format BPP2FIFormat(int bpp)
{
	Texture::Format result = Texture::Format::RGBA;
	switch (bpp) {
	case 8:
		result = Texture::Format::LUM;
		break;
	case 16:
		result = Texture::Format::LUMA;
		break;
	case 24:
		result = Texture::Format::BGR;
		break;
	case 32:
		result = Texture::Format::BGRA;
		break;
	}
	return result;
}

Texture::Texture()
: id(0),
  size(fei::Vec2(0.0f))
{
}

Texture::~Texture()
{
}

void Texture::loadFile(const char* filename)
{
	FIBITMAP *dib;
	if (!fei::isFileExist(filename)) {
		std::fprintf(stderr, "Texture: \"%s\" file not exist!\n", filename);
		return;
	}
	auto fif = FreeImage_GetFileType(filename, 0);
	if (FIF_UNKNOWN == fif) {
		fif = FreeImage_GetFIFFromFilename(filename);
	}
	if (FreeImage_FIFSupportsReading(fif)) {
		dib = FreeImage_Load(fif, filename, 0);
	} else {
		std::fprintf(stderr, "Texture: \"%s\" unsupported file!\n", filename);
		return;
	}
	auto bits = FreeImage_GetBits(dib);
	auto w = FreeImage_GetWidth(dib);
	auto h = FreeImage_GetHeight(dib);
	auto bpp = FreeImage_GetBPP(dib);
	Format format = BPP2FIFormat(bpp);
	loadData(bits, w, h, format);
	FreeImage_Unload(dib);
}

void Texture::loadData(const unsigned char* bits, int w, int h, Format dataFormat)
{
	GLenum internalFormat = GL_RGB;
	GLenum format = Format2GLFormat(dataFormat);
	if ((int)dataFormat % 2 == 0) {
		_isAlpha = true;
		internalFormat = GL_RGBA;
	} else {
		_isAlpha = false;
	}
	if (!id || GL_FALSE == glIsTexture(id)) {
		glGenTextures(1, &id);
	}
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h,
			0, format, GL_UNSIGNED_BYTE, bits);
	size = fei::Vec2(w, h);
}

void Texture::drawIt()
{
	fei::Render::getInstance()->bindTexture(id);
	fei::Render::getInstance()->drawTexQuad(size);
}
