#if !defined(_FEI_SHAPEOBJ_H_)
#define _FEI_SHAPEOBJ_H_

#include "math/Shape.h"
#include "render/RenderObj.h"

namespace fei {

class ShapeObj : public RenderObj
{
public:
	ShapeObj();

	void setShape(Shape* sp);
	void drawIt() override;

protected:
	Shape* shape;
};

} // namepsace fei

#endif // _FEI_SHAPEOBJ_H_
