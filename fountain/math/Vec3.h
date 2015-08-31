#if !defined(_FEI_VEC3_H_)
#define _FEI_VEC3_H_

#include "math/Vec2.h"

namespace fei {

class Vec3
{
public:
	explicit Vec3(float xyz);
	Vec3(float xx, float yy, float zz);
	Vec3(const Vec2& v, float zz);

	float x;
	float y;
	float z;
};

}

#endif