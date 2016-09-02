#include "render/ShapeObj.h"

#include "render/Render.h"

using fei::ShapeObj;

ShapeObj::ShapeObj()
: shape(nullptr)
{
}

void ShapeObj::setShape(fei::Shape* sp)
{
	shape = sp;
}

void ShapeObj::drawIt()
{
	if (shape != nullptr) {
		fei::Render::getInstance()->disableTexture();
		fei::Render::drawShape(shape);
	}
}
