#include "render/Image.h"

#include "render/Render.h"

using fei::Image;

Image::Image()
: id(0),
  size(fei::Vec2::ZERO),
  size2(fei::Vec2::ZERO)
{
	for (int i = 0; i < 8; i++) {
		texCoord[i] = 0.0f;
	}
}

Image::Image(const Image& img)
: id(0)
{
	*this = img;
}

void Image::operator=(const Image& img)
{
	fei::RenderObj::operator=(img);
	if (id != img.id) {
		fei::Render::getInstance()->releaseTexture(id);
		id = img.id;
		fei::Render::getInstance()->addRefTexture(id);
	}
	setHasAlpha(img.hasAlpha());
	setSize(img.size);
	for (int i = 0; i < 8; i++) {
		texCoord[i] = img.texCoord[i];
	}
}

Image::~Image()
{
	fei::Render::getInstance()->releaseTexture(id);
}

Image::Image(GLuint texId, const fei::Vec2& texSize, const fei::Rect& imageRect)
{
	fei::Render::getInstance()->addRefTexture(texId);
	auto rect = imageRect;
	id = texId;
	setSize(imageRect.getSize());
	rect.zoom(texSize.reciprocal());
	rect.getStripCoord(texCoord);
}

void Image::drawRect(const fei::Rect& rect)
{
	fei::Render::getInstance()->bindTexture(id);
	fei::Render::drawTexRect(rect, texCoord);
	fei::Render::getInstance()->disableTexture();
}

void Image::drawIt()
{
	fei::Render::getInstance()->bindTexture(id);
	fei::Render::drawTexQuadDS(size2, texCoord);
	fei::Render::getInstance()->disableTexture();
}

void Image::setSize(const fei::Vec2& s)
{
	size = s;
	size2 = size * 0.5f;
}

const fei::Vec2 Image::getSize() const
{
	return size;
}

const GLfloat* Image::getTextureCoord() const
{
	return texCoord;
}

bool Image::empty() const
{
	return (id == 0);
}

const fei::Vec2 Image::getLB()
{
	auto v = getTextureSize();
	v.zoom(fei::Vec2(texCoord[2], texCoord[3]));
	return v;
}

const fei::Vec2 Image::getTextureSize()
{
	return fei::Render::getInstance()->queryTexSize(id);
}

const Image Image::getImage(const fei::Rect& imageRect)
{
	auto rect = imageRect;
	rect.move(getLB());
	Image result = Image(id, getTextureSize(), rect);
	result.setHasAlpha(hasAlpha());
	return result;
}

const Image Image::getImage(const fei::Vec2& p, const fei::Vec2& s)
{
	return getImage(fei::Rect(p, s));
}

const Image Image::getImage()
{
	return *this;
}
