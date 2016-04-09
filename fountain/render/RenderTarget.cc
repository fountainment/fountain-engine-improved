#include "render/RenderTarget.h"

using fei::RenderTarget;

RenderTarget::RenderTarget(GLsizei width, GLsizei height)
: _width(0),
  _height(0)
{
	setSize(width, height);
}

fei::Texture* RenderTarget::getTexture()
{
	return &_texture;
}

void RenderTarget::setSize(GLsizei width, GLsizei height)
{
	//asert(width > 0 && height > 0)
	if (width != _width || height != _height) {
		_width = width;
		_height = height;
		_texture.load(nullptr, _width, _height);
	}
}
