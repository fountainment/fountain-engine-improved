#include "Image.h"
#include "render/Render.h"

using fei::Image;

Image::Image()
: id(0),
  size(fei::Vec2(0.0f))
{
	for (int i = 0; i < 8; i++) {
		texCoord[i] = 0.0f;
	}
}

Image::Image(GLuint texId, const fei::Vec2& texSize, const fei::Rect& imageRect)
{
	auto rectCopy = imageRect;
	id = texId;
	size = imageRect.getSize();
	rectCopy.zoom(texSize.reciprocal());
	rectCopy.getStripCoord(texCoord);
}

void Image::drawIt()
{
	fei::Render::getInstance()->bindTexture(id);
	fei::Render::getInstance()->drawTexQuad(size, texCoord);
}
