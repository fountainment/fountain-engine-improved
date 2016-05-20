#include "render/Texture.h"

#include <FreeImage.h>

#include "base/basedef.h"
#include "base/fileUtil.h"
#include "render/Render.h"

using fei::Texture;

static GLenum Format2GLFormat(Texture::Format format)
{
	static GLenum ToGLFormat[] = {0, GL_RGB, GL_RGBA, GL_BGR, GL_BGRA, GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA};
	return ToGLFormat[(int)format];
}

static GLenum Format2InternalFormat(Texture::Format format)
{
	static GLenum ToInternalFormat[] = {0, GL_RGB, GL_RGBA, GL_RGB, GL_RGBA, GL_RED, GL_RGBA, GL_RGB32F, GL_RGBA32F};
	return ToInternalFormat[(int)format];
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

static FIBITMAP* loadBitmap(const std::string& filename)
{
	FIBITMAP *dib;
	if (!fei::isFileExist(filename)) {
		std::fprintf(stderr, "Texture: \"%s\" file not exist!\n", filename.c_str());
		return nullptr;
	}
	auto fif = FreeImage_GetFileType(filename.c_str(), 0);
	if (FIF_UNKNOWN == fif) {
		fif = FreeImage_GetFIFFromFilename(filename.c_str());
	}
	if (FreeImage_FIFSupportsReading(fif)) {
		dib = FreeImage_Load(fif, filename.c_str(), 0);
	} else {
		std::fprintf(stderr, "Texture: \"%s\" unsupported file!\n", filename.c_str());
		return nullptr;
	}
	return dib;
}

Texture::Texture()
: _id(0),
  _size(fei::Vec2::ZERO),
  _size2(fei::Vec2::ZERO)
{
}

Texture::Texture(const Texture& tex)
: _id(0)
{
	(*this) = tex;
}

void Texture::operator=(const Texture& tex)
{
	fei::RenderObj::operator=(tex);
	setId(tex.getId());
}

Texture::~Texture()
{
	unload();
}

void Texture::load(const std::string& filename)
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
	fei::Render::getInstance()->registTexture(filename, _id);
	FreeImage_Unload(dib);
}

void Texture::load(const unsigned char* bits, int w, int h, Format dataFormat)
{
	GLenum internalFormat = Format2InternalFormat(dataFormat);
	GLenum format = Format2GLFormat(dataFormat);
	GLenum type = GL_UNSIGNED_BYTE;
	if (isLoaded()) {
		unload();
	}
	glGenTextures(1, &_id);
	fei::Render::getInstance()->addRefTexture(_id);
	glBindTexture(GL_TEXTURE_2D, _id);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	if (dataFormat == Format::RGBF || dataFormat == Format::RGBAF) {
		type = GL_FLOAT;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h,
		0, format, type, bits);
	setSize(fei::Vec2((float)w, (float)h));
	fei::Render::getInstance()->registTexSize(_id, _size);
}

void Texture::unload()
{
	fei::Render::getInstance()->releaseTexture(_id);
	_id = 0;
}

bool Texture::isLoaded() const
{
	return _id && GL_TRUE == glIsTexture(_id);
}

void Texture::subUpdate(const std::string& filename, int xoffset, int yoffset)
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
	glBindTexture(GL_TEXTURE_2D, _id);
	glTexSubImage2D(GL_TEXTURE_2D, 0, xoffset, yoffset, w, h,
			format, GL_UNSIGNED_BYTE, bits);
}

void Texture::drawIt()
{
	fei::Render::getInstance()->bindTexture(_id);
	fei::Render::drawTexQuadDS(_size2);
	fei::Render::getInstance()->disableTexture();
}

const fei::Image Texture::getImage(const fei::Rect& rect) const
{
	fei::Image result(_id, _size, rect);
	result.setHasAlpha(hasAlpha());
	return result;
}

const fei::Image Texture::getImage(const fei::Vec2& p, const fei::Vec2& s) const
{
	return getImage(fei::Rect(p, s));
}

const fei::Image Texture::getImage() const
{
	return getImage(fei::Vec2::ZERO, _size);
}

void Texture::setMinFilter(GLenum filter)
{
	GLint oldtex;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldtex);
	glBindTexture(GL_TEXTURE_2D, _id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glBindTexture(GL_TEXTURE_2D, oldtex);
}

void Texture::setMagFilter(GLenum filter)
{
	GLint oldtex;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldtex);
	glBindTexture(GL_TEXTURE_2D, _id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glBindTexture(GL_TEXTURE_2D, oldtex);
}

void Texture::bindLocation(int loc) const
{
	if (loc != 0) {
		glActiveTexture(GL_TEXTURE0 + loc);
	}
	glBindTexture(GL_TEXTURE_2D, _id);
	if (loc != 0) {
		glActiveTexture(GL_TEXTURE0);
	}
}

void Texture::generateMipmap()
{
	GLint oldtex;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldtex);
	glBindTexture(GL_TEXTURE_2D, _id);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, oldtex);
}

const fei::Vec2 Texture::getSize() const
{
	return _size;
}

GLuint Texture::getId() const
{
	return _id;
}

void Texture::setId(GLuint id)
{
	if (_id == id) return;
	if (isLoaded()) {
		unload();
	}
	setSize(fei::Render::getInstance()->queryTexSize(id));
	fei::Render::getInstance()->addRefTexture(id);
	_id = id;
}

void Texture::setSize(const fei::Vec2& sz)
{
	_size = sz;
	_size2 = sz * 0.5f;
}
