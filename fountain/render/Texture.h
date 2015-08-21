#if !defined(_FEI_TEXTURE_H_)
#define _FEI_TEXTURE_H_

#include "Render.h"
#include "render/RenderObj.h"
#include "render/Image.h"
#include "math/Vec2.h"
#include "math/Rect.h"
#include <GL/glew.h>

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
		LUMA = 6
	};

	friend class Render;

	Texture();
	virtual ~Texture();
	void loadFile(const char* filename);
	void loadData(const unsigned char* bits, int w, int h, Format dataFormat = Format::RGBA);

	const Image getImage(const Rect& rect);
	const Image getImage(const Vec2& p, const Vec2& s);
	const Image getImage();

	void drawIt() override;

private:
	GLuint id;
	Vec2 size;
};

}

#endif
