#include "Image.h"
#include "render/Render.h"

using fei::Image;

Image::Image()
: id(0)
{
	for (int i = 0; i < 8; i++) {
		texCoord[i] = 0.0f;
	}
}

void Image::drawIt()
{
	fei::Render::getInstance()->bindTexture(id);
	fei::Render::getInstance()->drawTexQuad(size, texCoord);
}
