#include "math/Rect.h"

using fei::Rect;

Rect::Rect()
{
	shapeType = fei::Shape::Type::RECT;
	size = fei::Vec2(1.0f);
}

Rect::Rect(const fei::Vec2& sz)
{
	shapeType = fei::Shape::Type::RECT;
	size = sz;
}

Rect::Rect(float x, float y, float w, float h)
{
	shapeType = fei::Shape::Type::RECT;
	pos = fei::Vec2(x, y);
	size = fei::Vec2(w, h);
	normalize();
}

Rect::Rect(const fei::Vec2& ps, const fei::Vec2& sz)
{
	shapeType = fei::Shape::Type::RECT;
	pos = ps;
	size = sz;
	normalize();
}

const fei::Vec2 Rect::getCenter() const
{
	return pos + size / 2.0f;
}

void Rect::setCenter(const fei::Vec2& p)
{
	pos = p - size / 2.0f;
}

const fei::Vec2 Rect::getSize() const
{
	return size;
}

void Rect::setSize(const fei::Vec2& sz)
{
	size = sz;
}

float Rect::getLeft()
{
	return pos.x;
}

float Rect::getRight()
{
	return pos.x + size.x;
}

float Rect::getTop()
{
	return pos.y + size.y;
}

float Rect::getBottom()
{
	return pos.y;
}

void Rect::zoom(float scale)
{
	pos.zoom(scale);
	size.zoom(scale);
}

void Rect::zoom(const fei::Vec2& v)
{
	pos.zoom(v);
	size.zoom(v);
}

void Rect::normalize()
{
	if (size.x < 0) {
		pos.x += size.x;
		size.x *= -1.0f;
	}
	if (size.y < 0) {
		pos.y += size.y;
		size.y *= -1.0f;
	}
}

bool Rect::collidePoint(const fei::Vec2& pt) const
{
	fei::Vec2 rt = pos + size;
	return ((pos.x - pt.x) * (rt.x - pt.x) <= 0) && ((pos.y - pt.y) * (rt.y - pt.y) <= 0);
}

void Rect::getStripCoord(float* coord) const
{
	auto rTop = pos + size;
	coord[0] = pos.x;
	coord[1] = rTop.y;
	coord[2] = pos.x;
	coord[3] = pos.y;
	coord[4] = rTop.x;
	coord[5] = rTop.y;
	coord[6] = rTop.x;
	coord[7] = pos.y;
}

const float* Rect::getDataPtr() const
{
	static float data[8] = {0.0f};
	data[2] = size.x;
	data[4] = size.x;
	data[5] = size.y;
	data[7] = size.y;
	return data;
}

int Rect::getDataSize() const
{
	return 4;
}
