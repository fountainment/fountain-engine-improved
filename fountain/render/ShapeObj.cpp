#include "ShapeObj.h"
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
	fei::Render::drawShape(shape);
}
