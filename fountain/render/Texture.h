#if !defined(_FEI_TEXTURE_H_)
#define _FEI_TEXTURE_H_

#include "Render.h"
#include "RenderObj.h"
#include "math/Vec2.h"
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
	~Texture();
	void loadFile(const char* filename);
	void loadData(const unsigned char* bits, int w, int h, Format dataFormat = Format::RGBA);
	void draw();

private:
	GLuint id;
	int width;
	int height;
};

}

#endif
