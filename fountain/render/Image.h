#if !defined(_FEI_IMAGE_H_)
#define _FEI_IMAGE_H_

#include "render/RenderObj.h"
#include "math/Vec2.h"
#include "math/Rect.h"
#include <GL/glew.h>

namespace fei {

class Image : public RenderObj
{
public:
	Image();
	Image(GLuint texId, const Vec2& texSize, const Rect& imageRect);
	void drawIt() override;

private:
	GLuint id;
	Vec2 size;
	GLfloat texCoord[8];

};

}

#endif
