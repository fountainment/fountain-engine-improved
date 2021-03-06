#include "render/Color.h"

#include "render/Render.h"

using fei::Color;

static int HexToDec(const std::string& str, int len = -1)
{
	int ans = 0;
	int strLength = len;
	if (strLength == -1) {
		strLength = str.length();
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
	fei::Vec3 result(fei::Vec3::ZERO);
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
			} else if (len == 7) {
				result.x = (float)HexToDec(cstr + 1, 2);
				result.y = (float)HexToDec(cstr + 3, 2);
				result.z = (float)HexToDec(cstr + 5, 2);
				result /= 255.0f;
			} else {
				throw "Length incorrect!";
			}
		}
	} catch(const std::string& str) {
		std::fprintf(stderr, "Color string format error: %s\n", str.c_str());
		assert(0);
	}
	return result;
}

Color::Color(float rgb)
{
	x = y = z = rgb;
	w = 1.0f;
}

Color::Color(float rr, float gg, float bb, float aa)
{
	x = rr;
	y = gg;
	z = bb;
	w = aa;
}

Color::Color(const fei::Vec3& rgb, float aa)
{
	setRGB(rgb);
	w = aa;
}

Color::Color(const std::string& colorStr, float aa)
{
	setRGB(colorStr);
	w = aa;
}

void Color::setRGB(const fei::Vec3& rgb)
{
	x = rgb.x;
	y = rgb.y;
	z = rgb.z;
}

void Color::setRGB(const std::string& colorStr)
{
	setRGB(strToRGB(colorStr));
}

void Color::toGrayScale()
{
	x = y = z = x * .299f + y * .587f + z * .114f;
}

void Color::toInverse()
{
	x = 1.0f - x;
	y = 1.0f - y;
	z = 1.0f - z;
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

void Color::setClearColor() const
{
	fei::Render::getInstance()->setClearColor(this);
}

const Color Color::Red    = Color(1.0f, 0.0f, 0.0f);
const Color Color::Green  = Color(0.0f, 1.0f, 0.0f);
const Color Color::Blue   = Color(0.0f, 0.0f, 1.0f);
const Color Color::Black  = Color(0.0f);
const Color Color::White  = Color(1.0f);
const Color Color::Yellow = Color(1.0f, 1.0f, 0.0f);
const Color Color::Orange = Color(1.0f, 0.5f, 0.0f);
const Color Color::Gray   = Color(0.5f);
