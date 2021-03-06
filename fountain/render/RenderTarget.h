#ifndef _FEI_RENDERTARGET_H_
#define _FEI_RENDERTARGET_H_

#include <glad/glad.h> 

#include "base/basedef.h"
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

	Vec2 getSize();

	void bindColorAttachment(Texture* texture, int attachIndex);
	void setDrawBuffers(const std::vector<GLenum>& buffers);

	void bind();
	void unbind();

	bool isBind();

	float getHDRLw();

	void fillWithTexture(Texture* texture);

private:
	void genBuffers();
	void deleteBuffers();
	void tmpBind();
	void tmpUnbind();

	GLuint _renderbuffer, _framebuffer;
	GLsizei _width, _height;
	bool _tmpBind;
	Texture _texture;

	static std::vector<GLfloat> computeBuffer_;
};

} // namespace fei

#endif // _FEI_RENDERTARGET_H_
