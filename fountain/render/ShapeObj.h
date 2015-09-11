#if !defined(_FEI_SHAPEOBJ_H_)
#define _FEI_SHAPEOBJ_H_

#include "render/RenderObj.h"
#include "math/Shape.h"

namespace fei {

class ShapeObj : public RenderObj
{
public:
	ShapeObj();

	void setShape(Shape* sp);
	void drawIt() override;

private:
	Shape* shape;
};

}

#endif
