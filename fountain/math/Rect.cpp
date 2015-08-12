#include "Rect.h"

using fei::Rect;

Rect::Rect(float x, float y, float w, float h)
{
	position = fei::Vec2(x, y);
	size = fei::Vec2(w, h);
}

Rect::Rect(fei::Vec2 pos, fei::Vec2 sz)
{
	position = pos;
	size = sz;
}

fei::Vec2 Rect::getCenter()
{
	return (position + size) / 2.0f;
}
