#ifndef _FEI_RENDERTARGET_H_
#define _FEI_RENDERTARGET_H_

#include <GL/glew.h>

#include "math/Vec2.h"
#include "render/Texture.h"

namespace fei {

class RenderTarget
{
public:
	RenderTarget();
	~RenderTarget();
	RenderTarget(const Vec2& size);
	RenderTarget(GLsizei width, GLsizei height);

	Texture* getTexture();

	void setSize(const Vec2& size, Texture::Format format = Texture::Format::RGBA);
	void setSize(GLsizei width, GLsizei height, Texture::Format format = Texture::Format::RGBA);

	void bindColorAttachment(Texture* texture, int attachIndex);

	void bind();
	void unbind();

	bool isBind();

	float getHDRLw();

private:
	void genBuffers();
	void deleteBuffers();

	GLuint _renderbuffer, _framebuffer;
	GLsizei _width, _height;
	bool _isBind;
	Texture _texture;
};

} // namespace fei

#endif // _FEI_RENDERTARGET_H_
