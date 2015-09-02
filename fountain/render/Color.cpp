#include "Color.h"
#include "render/Render.h"

using fei::Color;

Color::Color()
{
	r = g = b = a = 1.0f;
}

Color::Color(float rgb)
{
	r = g = b = rgb;
	a = 1.0f;
}

Color::Color(float rr, float gg, float bb, float aa)
{
	r = rr;
	g = gg;
	b = bb;
	a = aa;
}

Color::Color(const Vec3& rgb, float aa)
{
	r = rgb.x;
	g = rgb.y;
	b = rgb.z;
	a = aa;
}

Color& Color::operator=(const Color& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;
	return *this;
}

void Color::toGrayScale()
{
	r = g = b = r * .299f + g * .587f + b * .114f; 
}

void Color::toInverse()
{
	r = 1.0f - r;
	g = 1.0f - g;
	b = 1.0f - b;
}

const Color Color::grayScaled() const
{
	Color color(*this);
	color.toGrayScale();
	return color;
}

const Color Color::inversed() const
{
	Color color(*this);
	color.toInverse();
	return color;
}

void Color::use() const
{
	fei::Render::getInstance()->useColor(this);
}

const Color Color::Red    = Color(1.0f, 0.0f, 0.0f);
const Color Color::Green  = Color(0.0f, 1.0f, 0.0f);
const Color Color::Blue   = Color(0.0f, 0.0f, 1.0f);
const Color Color::Black  = Color(0.0f);
const Color Color::White  = Color(1.0f);
const Color Color::Yellow = Color(1.0f, 1.0f, 0.0f);
const Color Color::Orange = Color(1.0f, 0.5f, 0.0f);
const Color Color::Gray   = Color(0.5f);