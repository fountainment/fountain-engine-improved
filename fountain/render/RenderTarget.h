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
	RenderTarget(const Vec2& size);
	RenderTarget(GLsizei width, GLsizei height);

	Texture* getTexture();

	void setSize(const Vec2& size);
	void setSize(GLsizei width, GLsizei height);

	void bind();
	void unbind();

private:
	GLuint _renderbuffer, _framebuffer;
	GLsizei _width, _height;
	Texture _texture;
};

} // namespace fei

#endif // _FEI_RENDERTARGET_H_
