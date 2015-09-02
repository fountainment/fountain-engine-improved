#if !defined(_FEI_VEC4_H_)
#define _FEI_VEC4_H_

#include "math/Vec3.h"

namespace fei {

class Vec4
{
public:
	Vec4();
	explicit Vec4(float xyzw);
	Vec4(float xx, float yy, float zz, float ww);
	Vec4(const Vec3& xyz, float ww);

	float x;
	float y;
	float z;
	float w;
};

}

#endif