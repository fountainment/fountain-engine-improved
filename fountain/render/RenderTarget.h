#ifndef _FEI_RENDERTARGET_H_
#define _FEI_RENDERTARGET_H_

#include <GL/glew.h>

#include "render/Texture.h"

namespace fei {

class RenderTarget 
{
public:
	RenderTarget(GLsizei width, GLsizei height);

	Texture* getTexture();
	
	void setSize(GLsizei width, GLsizei height);

private:
	RenderTarget() = default;

	GLsizei _width, _height;
	Texture _texture;
};

} // namespace fei

#endif // _FEI_RENDERTARGET_H_
