#if !defined(_FEI_CIRCLE_H_)
#define _FEI_CIRCLE_H_

#include "base/basedef.h"
#include "math/Shape.h"
#include "math/Vec2.h"

namespace fei {

class Circle : public Shape
{
public:
	Circle();
	explicit Circle(float r);

	int getDataSize() const override;
	const float* getDataPtr() const override;

	float getRadius() const;
	void setRadius(float r);

	bool collide(const Shape* shape) const override;

private:
	float radius;

	static std::vector<Vec2> data32;
	static std::vector<Vec2> data64;
};

} // namespace fei

#endif _FEI_CIRCLE_H_
