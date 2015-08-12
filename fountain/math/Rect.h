#if !defined(_FEI_RECT_H_)
#define _FEI_RECT_H_

#include "Vec2.h"

namespace fei {

class Rect
{
public:
	Rect(float x, float y, float w, float h);
	Rect(Vec2 pos, Vec2 sz);

	Vec2 position;
	Vec2 size;

	Vec2 getCenter();
	//TODO:
};

}

#endif
