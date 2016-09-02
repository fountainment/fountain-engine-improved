#include "render/Image.h"

#include "render/Render.h"

using fei::Image;

Image::Image()
: _id(0),
  _size(fei::Vec2::ZERO),
  _size2(fei::Vec2::ZERO)
{
	for (int i = 0; i < 8; i++) {
		_texCoord[i] = 0.0f;
	}
}

Image::Image(const Image& img)
: _id(0)
{
	*this = img;
}

void Image::operator=(const Image& img)
{
	fei::RenderObj::operator=(img);
	if (getId() != img.getId()) {
		fei::Render::getInstance()->releaseTexture(getId());
		setId(img.getId());
		fei::Render::getInstance()->addRefTexture(getId());
	}
	setHasAlpha(img.hasAlpha());
	setSize(img.getSize());
	for (int i = 0; i < 8; i++) {
		_texCoord[i] = img._texCoord[i];
	}
}

Image::~Image()
{
	fei::Render::getInstance()->releaseTexture(getId());
}

Image::Image(GLuint texId, const fei::Vec2& texSize, const fei::Rect& imageRect)
{
	fei::Render::getInstance()->addRefTexture(texId);
	auto rect = imageRect;
	setId(texId);
	setSize(imageRect.getSize());
	rect.zoom(texSize.reciprocal());
	rect.getStripCoord(_texCoord);
}

void Image::drawRect(const fei::Rect& rect)
{
	fei::Render::getInstance()->bindTexture(getId());
	fei::Render::drawTexRect(rect, _texCoord);
}

void Image::drawIt()
{
	fei::Render::getInstance()->bindTexture(getId());
	fei::Render::drawTexQuadDS(_size2, _texCoord);
}

void Image::fillUp()
{
	auto camera = fei::Render::getInstance()->getCurrentCamera();
	auto viewport = fei::Render::getInstance()->getViewport();
	auto target = fei::Render::getInstance()->getCurrentRenderTarget();
	if (target) {
		fei::Render::getInstance()->setViewport(target->getSize());
	}
	drawRect(camera->getCameraRect());
	fei::Render::getInstance()->setViewport(viewport);
}

void Image::setSize(const fei::Vec2& s)
{
	_size = s;
	_size2 = s * 0.5f;
}

const fei::Vec2 Image::getLB()
{
	auto v = getTextureSize();
	v.zoom(fei::Vec2(_texCoord[2], _texCoord[3]));
	return v;
}

const fei::Vec2 Image::getTextureSize()
{
	return fei::Render::getInstance()->queryTexSize(getId());
}

const fei::Rect Image::getTextureCoordRect()
{
	return fei::Rect(_texCoord[0], _texCoord[3], \
			_texCoord[4] - _texCoord[0], _texCoord[1] - _texCoord[3]);
}

const fei::Rect Image::getTexturePixelRect()
{
	return getTextureCoordRect().zoomed(getTextureSize());
}

const Image Image::getImage(const fei::Rect& imageRect)
{
	auto rect = imageRect;
	rect.move(getLB());
	Image result = Image(getId(), getTextureSize(), rect);
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
