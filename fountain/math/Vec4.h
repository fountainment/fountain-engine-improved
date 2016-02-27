#if !defined(_FEI_VEC4_H_)
#define _FEI_VEC4_H_

//TODO: add Vec4 calculation functions

#include "math/Vec3.h"

namespace fei {

class Vec4
{
public:
	Vec4() = default;
	explicit Vec4(float xyzw);
	Vec4(float xx, float yy, float zz, float ww);
	Vec4(const Vec3& xyz, float ww);

	float x;
	float y;
	float z;
	float w;
};

} // namespace fei

#endif // _FEI_VEC4_H_
