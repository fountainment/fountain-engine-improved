#ifndef _FEI_MATHDEF_H_
#define _FEI_MATHDEF_H_

#include "base/basedef.h"

namespace fei {

extern const double eps;
extern const float epsf;
extern const double pi;
extern const float pif;

extern const double d2r;
extern const double r2d;

inline double D2R(double degree)
{
	return degree * d2r;
}

inline double R2D(double rad)
{
	return rad * r2d;
}

} // namespace fei

#endif // _FEI_MATHDEF_H_
