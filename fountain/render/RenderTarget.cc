#include "render/RenderTarget.h"

#include <glad/glad.h>

#include "base/basedef.h"
#include "math/mathdef.h"
#include "render/Render.h"

using fei::RenderTarget;

RenderTarget::RenderTarget()
: _renderbuffer(0),
  _framebuffer(0),
  _width(0),
  _height(0),
  _tmpBind(false)
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
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		tmpBind();
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, getTexture()->getId(), 0);
		glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _renderbuffer);
		tmpUnbind();
	}
}

void RenderTarget::bindColorAttachment(fei::Texture* texture, int attachIndex)
{
	GLuint texId = 0;
	if (texture != nullptr) {
		texId = texture->getId();
	}
	tmpBind();
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachIndex, GL_TEXTURE_2D, texId, 0);
	tmpUnbind();
}

void RenderTarget::setDrawBuffers(const std::vector<GLenum>& buffers)
{
	tmpBind();
	glDrawBuffers(static_cast<GLsizei>(buffers.size()), &(buffers[0]));
	tmpUnbind();
}

void RenderTarget::bind()
{
	if (!isBind()) {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _framebuffer);
		fei::Render::getInstance()->setCurrentRenderTarget(this);
	}
}

void RenderTarget::unbind()
{
	if (isBind()) {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		fei::Render::getInstance()->setCurrentRenderTarget(nullptr);
	}
}

bool RenderTarget::isBind()
{
	return fei::Render::getInstance()->getCurrentRenderTarget() == this;
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
		float l = buffer[i + 3] * 0.2126f + buffer[i + 2] * 0.7152f + buffer[i + 1] * 0.0722f;
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

void RenderTarget::tmpBind()
{
	if (!isBind()) {
		bind();
		_tmpBind = true;
	}
}

void RenderTarget::tmpUnbind()
{
	if (_tmpBind) {
		unbind();
		_tmpBind = false;
	}
}
