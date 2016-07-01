#ifndef _FEI_MATHDEF_H_
#define _FEI_MATHDEF_H_

#include "base/basedef.h"

namespace fei {

extern const double eps;
extern const float epsf;

extern const double pi;
extern const float pif;

extern const double d2r;
extern const float d2rf;

extern const double r2d;
extern const float r2df;

inline double D2R(double degree)
{
	return degree * d2r;
}

inline double R2D(double rad)
{
	return rad * r2d;
}

inline float D2Rf(float degree)
{
	return degree * d2rf;
}

inline float R2Df(float rad)
{
	return rad * r2df;
}

template <class T>
inline T MAX(T a, T b)
{
	return a>b?a:b;
}

template <class T>
inline T MAX(T a, T b, T c)
{
	return MAX(MAX(a, b), c);
}

template <class T>
inline T MIN(T a, T b)
{
	return a<b?a:b;
}

template <class T>
inline T MIN(T a, T b, T c)
{
	return MIN(MIN(a, b), c);
}

} // namespace fei

#endif // _FEI_MATHDEF_H_
