#include "Rect.h"

using fei::Rect;

Rect::Rect(float x, float y, float w, float h)
{
	position = Vec2(x, y);
	size = Vec2(w, h);
}

Rect::Rect(Vec2 pos, Vec2 sz)
{
	position = pos;
	size = sz;
}

fei::Vec2 Rect::getCenter()
{
	return (position + size) / 2.0f;
}
