#include "Color.h"
#include "render/Render.h"

using fei::Color;

static int HexToDec(const char* str, int len = -1)
{
	int ans = 0;
	int strLength = len;
	if (strLength == -1) {
		strLength = std::strlen(str);
	}
	for (int i = 0; i < strLength; i++) {
		if (i != 0) {
			ans *= 16;
		}
		int tmp = 0;
		if (str[i] >= 'a' && str[i] <= 'f') {
			tmp = str[i] - 'a' + 10;
		} else if (str[i] >= 'A' && str[i] <= 'F') {
			tmp = str[i] - 'A' + 10;
		} else if (str[i] >= '0' && str[i] <= '9') {
			tmp = str[i] - '0';
		} else {
			throw "String unavailable!";
		}
		ans += tmp;
	}
	return ans;
}

static const fei::Vec3 strToRGB(const std::string& colorStr)
{
	int len = colorStr.length();
	const char* cstr = colorStr.c_str();
	fei::Vec3 result;
	try {
		if (len <= 3) {
			throw "Length less than 3!";
		}
		if (colorStr[0] == '#') {
			if (len == 4) {
				result.x = (float)HexToDec(cstr + 1, 1);
				result.y = (float)HexToDec(cstr + 2, 1);
				result.z = (float)HexToDec(cstr + 3, 1);
				result = (result * 16.0f + result) / 255.0f;
			} else if (len == 6) {
				result.x = (float)HexToDec(cstr + 1, 2);
				result.y = (float)HexToDec(cstr + 3, 2);
				result.z = (float)HexToDec(cstr + 5, 2);
				result /= 255.0f;
			} else {
				throw "Length incorrect!";
			}
		}
	} catch(const std::string& str) {
		std::printf("Color string format error: %s\n", str.c_str());
		assert(0);
	}
	return result;
}

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

Color::Color(const fei::Vec3& rgb, float aa)
{
	setRGB(rgb);
	a = aa;
}

Color::Color(const std::string& colorStr, float aa)
{
	setRGB(colorStr);
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

void Color::setRGB(const fei::Vec3& rgb)
{
	r = rgb.x;
	g = rgb.y;
	b = rgb.z;
}

void Color::setRGB(const std::string& colorStr)
{
	setRGB(strToRGB(colorStr));
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
