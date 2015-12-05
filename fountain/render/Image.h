#if !defined(_FEI_IMAGE_H_)
#define _FEI_IMAGE_H_

#include <GL/glew.h>

#include "math/Rect.h"
#include "math/Vec2.h"
#include "render/RenderObj.h"

namespace fei {

class Image : public RenderObj
{
public:
	Image();
	Image(const Image& img);
	void operator=(const Image& img);

	~Image();
	Image(GLuint texId, const Vec2& texSize, const Rect& imageRect);

	void drawRect(const Rect& rect);

	void drawIt() override;

	const Vec2 getSize() const;
	const GLfloat* getTextureCoord() const;

	bool empty() const;
	
	const Image getImage(const Rect& imageRect);
	const Image getImage(const Vec2& p, const Vec2& s);
	const Image getImage();

private:
	GLuint id;
	Vec2 size;
	Vec2 size2;
	GLfloat texCoord[8];

	void setSize(const Vec2& s);

	const fei::Vec2 getLB();
	const fei::Vec2 getTextureSize();
};

} // namespace fei

#endif // _FEI_IMAGE_H_
