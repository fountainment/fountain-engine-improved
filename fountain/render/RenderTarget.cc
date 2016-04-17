#include "render/RenderTarget.h"

#include  <GL/glew.h>

#include "base/basedef.h"
#include "math/mathdef.h"

using fei::RenderTarget;

RenderTarget::RenderTarget()
: _renderbuffer(0),
  _framebuffer(0),
  _width(0),
  _height(0),
  _isBind(false)
{
}

RenderTarget::~RenderTarget()
{
	deleteBuffers();
}

RenderTarget::RenderTarget(const fei::Vec2& size)
: RenderTarget()
{
	setSize(size);
}

RenderTarget::RenderTarget(GLsizei width, GLsizei height)
: RenderTarget()
{
	setSize(width, height);
}

fei::Texture* RenderTarget::getTexture()
{
	return &_texture;
}

void RenderTarget::setSize(const fei::Vec2& size, fei::Texture::Format format)
{
	setSize(static_cast<GLsizei>(size.x), static_cast<GLsizei>(size.y), format);
}

void RenderTarget::setSize(GLsizei width, GLsizei height, fei::Texture::Format format)
{
	if (width == 0 || height == 0) {
		return;
	}
	if (width != _width || height != _height) {
		_width = width;
		_height = height;
		_texture.load(nullptr, width, height, format);
		genBuffers();

		glBindRenderbuffer(GL_RENDERBUFFER, _renderbuffer);
		bind();
		bindColorAttachment(getTexture(), 0);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);

		glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _renderbuffer);
		unbind();
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}

void RenderTarget::bindColorAttachment(fei::Texture* texture, int attachIndex)
{
	GLuint texId = 0;
	if (texture != nullptr) {
		texId = texture->getId();
	}
	if (isBind()) {
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachIndex, GL_TEXTURE_2D, texId, 0);
	} else {
		bind();
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachIndex, GL_TEXTURE_2D, texId, 0);
		unbind();
	}
}

void RenderTarget::bind()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _framebuffer);
	_isBind = true;
}

void RenderTarget::unbind()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	_isBind = false;
}

bool RenderTarget::isBind()
{
	return _isBind;
}

float RenderTarget::getHDRLw()
{
	float ret = 0.0f;
	auto size = _texture.getSize();
	GLuint w = size.x;
	GLuint h = size.y;
	GLfloat* buffer = new GLfloat[w * h * 4];
	glBindFramebuffer(GL_READ_FRAMEBUFFER, _framebuffer);
	glReadPixels(0, 0, w, h, GL_RGBA, GL_FLOAT, buffer);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	float sum = 0.0f;
	for (int i = 0; i < int(w * h * 4); i += 4) {
		float l = buffer[i] * 0.2126f + buffer[i + 1] * 0.7152f + buffer[i + 2] * 0.0722f;
		sum += std::log(fei::epsf + l);
	}
	ret = std::exp(sum / (size.x * size.y));
	delete [] buffer;
	return ret;
}

void RenderTarget::genBuffers()
{
	if (_renderbuffer == 0) {
		glGenRenderbuffers(1, &_renderbuffer);
	}
	if (_framebuffer == 0) {
		glGenFramebuffers(1, &_framebuffer);
	}
}

void RenderTarget::deleteBuffers()
{
	if (isBind()) {
		unbind();
	}
	if (_framebuffer != 0) {
		glDeleteFramebuffers(1, &_framebuffer);
		_framebuffer = 0;
	}
	if (_renderbuffer != 0) {
		glDeleteRenderbuffers(1, &_renderbuffer);
		_renderbuffer = 0;
	}
}
