#if !defined(_FEI_COLOR_H_)
#define _FEI_COLOR_H_

#include "math/Vec4.h"
#include "base/basedef.h"

namespace fei {

class Color : public Vec4
{
public:
	float &r = x;
	float &g = y;
	float &b = z;
	float &a = w;

	Color();
	Color(float rgb);
	Color(float rr, float gg, float bb, float aa = 1.0f);
	Color(const std::string& colorStr, float aa = 1.0f);
	Color(const Vec3& rgb, float aa = 1.0f);

	Color& operator=(const Color& rhs);

	void setRGB(const Vec3& rgb);
	void setRGB(const std::string& colorStr);

	void toGrayScale();
	void toInverse();

	const Color grayScaled() const;
	const Color inversed() const;

	void use() const;

	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Black;
	static const Color White;
	static const Color Yellow;
	static const Color Orange;
	static const Color Gray;
};

} // namespace fei

#endif // _FEI_COLOR_H_ 
