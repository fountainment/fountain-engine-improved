#ifndef _FEI_MATHDEF_H_
#define _FEI_MATHDEF_H_

#include "base/basedef.h"

namespace fei {

constexpr double eps = 1e-8;
constexpr float epsf = 1e-5f;

constexpr double pi = 3.14159265358979324;
constexpr float pif = 3.14159265358979324f;

constexpr double d2r = 0.017453292519943;
constexpr float d2rf = 0.017453292519943f;

constexpr double r2d = 57.295779513082;
constexpr float r2df = 57.295779513082f;

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

template <class T>
inline T clamp(T origin, T a, T b)
{
	if (origin < a) return a;
	if (origin > b) return b;
	return origin;
}

template <class T>
inline int cmp(T a, T b) {
	if (a == b) return 0;
	return a < b ? -1 : 1;
}

} // namespace fei

#endif // _FEI_MATHDEF_H_
