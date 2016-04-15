#ifndef _FEI_TEXTURE_H_
#define _FEI_TEXTURE_H_

#include <GL/glew.h>

#include "render/Image.h"
#include "render/Render.h"
#include "render/RenderObj.h"
#include "math/Rect.h"
#include "math/Vec2.h"

namespace fei {

class Texture : public fei::RenderObj
{
public:
	enum class Format {
		RGB = 1,
		RGBA = 2,
		BGR = 3,
		BGRA = 4,
		LUM = 5,
		LUMA = 6,
		RGBF = 7,
		RGBAF = 8
	};

	Texture();
	Texture(const Texture& tex);
	void operator=(const Texture& tex);

	virtual ~Texture();

	void load(const std::string& filename);
	void load(const unsigned char* bits, int w, int h, Format dataFormat = Format::RGBA);
	void unload();

	bool isLoaded() const;

	void subUpdate(const std::string& filename, int xoffset, int yoffset);
	void subUpdate(const unsigned char* bits, int w, int h, Format dataFormat, int xoffset, int yoffset);

	const Image getImage(const Rect& rect) const;
	const Image getImage(const Vec2& p, const Vec2& s) const;
	const Image getImage() const;

	void setMinFilter(GLenum filter);
	void setMagFilter(GLenum filter);
	void bindLocation(int loc) const;

	const Vec2 getSize() const;
	GLuint getId() const;

	void drawIt() override;

private:
	void setId(GLuint _id);
	void setSize(const Vec2& s);

	GLuint _id;
	Vec2 _size;
	Vec2 _size2;
};

} // namespace fei

#endif // _FEI_TEXTURE_H_
