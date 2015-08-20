#if !defined(_FEI_IMAGE_H_)
#define _FEI_IMAGE_H_

#include "render/RenderObj.h"
#include <GL/glew.h>

namespace fei {

class Image : public RenderObj
{
private:
	GLuint id;
	Vec2 size;
	GLfloat texCoord[8];
	void drawIt() override;

public:
	Image();
};

}

#endif
