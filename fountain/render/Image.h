#ifndef _FEI_IMAGE_H_
#define _FEI_IMAGE_H_

#include <glad/glad.h>

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

	const fei::Vec2 getTextureSize();
	const fei::Rect getTextureCoordRect();
	const fei::Rect getTexturePixelRect();

private:
	GLuint _id;
	Vec2 _size;
	Vec2 _size2;
	GLfloat _texCoord[8];

	GLuint getId() const;
	void setId(GLuint id);
	void setSize(const Vec2& s);

	const fei::Vec2 getLB();
};

} // namespace fei

inline const fei::Vec2 fei::Image::getSize() const
{
	return _size;
}

inline const GLfloat* fei::Image::getTextureCoord() const
{
	return _texCoord;
}

inline bool fei::Image::empty() const
{
	return (getId() == 0);
}

inline GLuint fei::Image::getId() const
{
	return _id;
}

inline void fei::Image::setId(GLuint id)
{
	_id = id;
}

#endif // _FEI_IMAGE_H_
