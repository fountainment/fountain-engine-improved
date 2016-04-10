#include "render/RenderTarget.h"

#include  <GL/glew.h>

using fei::RenderTarget;

RenderTarget::RenderTarget()
: _renderbuffer(0),
  _framebuffer(0),
  _width(0),
  _height(0)
{
}

RenderTarget::RenderTarget(const fei::Vec2& size)
{
	setSize(size);
}

RenderTarget::RenderTarget(GLsizei width, GLsizei height)
{
	setSize(width, height);
}

fei::Texture* RenderTarget::getTexture()
{
	return &_texture;
}

void RenderTarget::setSize(const fei::Vec2& size)
{
	setSize(static_cast<GLsizei>(size.x), static_cast<GLsizei>(size.y));
}

void RenderTarget::setSize(GLsizei width, GLsizei height)
{
	//TODO: asert(width > 0 && height > 0)
	if (width != _width || height != _height) {
		_width = width;
		_height = height;
		_texture.load(nullptr, width, height);

		if (_renderbuffer == 0) {
			glGenRenderbuffers(1, &_renderbuffer);
		}
		glBindRenderbuffer(GL_RENDERBUFFER, _renderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);

		if (_framebuffer == 0) {
			glGenFramebuffers(1, &_framebuffer);
		}
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _framebuffer);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, getTexture()->getId(), 0);
		glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _renderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}
}

void RenderTarget::bind()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _framebuffer);
}

void RenderTarget::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
