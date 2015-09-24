#include "Texture.h"
#include "base/basedef.h"
#include "base/fileUtil.h"
#include "render/Render.h"
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

static FIBITMAP* loadBitmap(const char* filename)
{
	FIBITMAP *dib;
	if (!fei::isFileExist(filename)) {
		std::fprintf(stderr, "Texture: \"%s\" file not exist!\n", filename);
		return nullptr;
	}
	auto fif = FreeImage_GetFileType(filename, 0);
	if (FIF_UNKNOWN == fif) {
		fif = FreeImage_GetFIFFromFilename(filename);
	}
	if (FreeImage_FIFSupportsReading(fif)) {
		dib = FreeImage_Load(fif, filename, 0);
	} else {
		std::fprintf(stderr, "Texture: \"%s\" unsupported file!\n", filename);
		return nullptr;
	}
	return dib;
}

Texture::Texture()
: id(0),
  size(fei::Vec2::ZERO)
{
}

Texture::Texture(const Texture& tex)
: id(0)
{
	(*this) = tex;
}

void Texture::operator=(const Texture& tex)
{
	setIsAlpha(tex.isAlpha());
	setId(tex.id);
}

Texture::~Texture()
{
	unload();
}

void Texture::load(const char* filename)
{
	int queryId = fei::Render::getInstance()->queryTexture(filename);
	if (queryId) {
		setId(queryId);
		return;
	}
	auto dib = loadBitmap(filename);
	if (!dib) {
		return;
	}
	auto bits = FreeImage_GetBits(dib);
	int w = FreeImage_GetWidth(dib);
	int h = FreeImage_GetHeight(dib);
	int bpp = FreeImage_GetBPP(dib);
	Format format = BPP2FIFormat(bpp);
	load(bits, w, h, format);
	fei::Render::getInstance()->registTexture(filename, id);
	FreeImage_Unload(dib);
}

void Texture::load(const unsigned char* bits, int w, int h, Format dataFormat)
{
	GLenum internalFormat = GL_RGB;
	GLenum format = Format2GLFormat(dataFormat);
	if ((int)dataFormat % 2 == 0) {
		internalFormat = GL_RGBA;
	}
	if (!isLoaded()) {
		glGenTextures(1, &id);
		fei::Render::getInstance()->addRefTexture(id);
	}
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h,
			0, format, GL_UNSIGNED_BYTE, bits);
	size = fei::Vec2((float)w, (float)h);
	fei::Render::getInstance()->registTexSize(id, size);
}

void Texture::unload()
{
	fei::Render::getInstance()->releaseTexture(id);
	id = 0;
}

bool Texture::isLoaded() const
{
	return id && GL_TRUE == glIsTexture(id);
}

void Texture::subUpdate(const char* filename, int xoffset, int yoffset)
{
	if (!isLoaded()) {
		return;
	}
	auto dib = loadBitmap(filename);
	if (!dib) {
		return;
	}
	auto bits = FreeImage_GetBits(dib);
	int w = FreeImage_GetWidth(dib);
	int h = FreeImage_GetHeight(dib);
	int bpp = FreeImage_GetBPP(dib);
	Format format = BPP2FIFormat(bpp);
	subUpdate(bits, w, h, format, xoffset, yoffset);
	FreeImage_Unload(dib);
}

void Texture::subUpdate(const unsigned char* bits, int w, int h, Format dataFormat, int xoffset, int yoffset)
{
	if (!isLoaded()) {
		return;
	}
	GLenum format = Format2GLFormat(dataFormat);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexSubImage2D(GL_TEXTURE_2D, 0, xoffset, yoffset, w, h,
			format, GL_UNSIGNED_BYTE, bits);
}

void Texture::drawIt()
{
	fei::Render::getInstance()->bindTexture(id);
	fei::Render::getInstance()->drawTexQuad(size);
	fei::Render::getInstance()->disableTexture();
}

const fei::Image Texture::getImage(const fei::Rect& rect) const
{
	fei::Image result(id, size, rect);
	result.setIsAlpha(isAlpha());
	return result;
}

const fei::Image Texture::getImage(const fei::Vec2& p, const fei::Vec2& s) const
{
	return getImage(fei::Rect(p, s));
}

const fei::Image Texture::getImage() const
{
	return getImage(fei::Vec2::ZERO, size);
}

void Texture::setId(GLuint _id)
{
	if (id == _id) return;
	if (isLoaded()) {
		unload();
	}
	size = fei::Render::getInstance()->queryTexSize(_id);
	fei::Render::getInstance()->addRefTexture(_id);
	id = _id;
}
