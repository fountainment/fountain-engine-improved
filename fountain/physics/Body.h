#if !defined(_FEI_BODY_H_)
#define _FEI_BODY_H_

#include <Box2D/Box2D.h>
#include "math/Vec2.h"
#include "math/Shape.h"

namespace fei {

class Body
{
public:
	friend class Physics;

	enum class Type {
		STATIC = 1,
		DYNAMIC = 2,
		KINEMATIC = 3
	};

	const fei::Vec2 getPosition() const;
	float getAngle() const;

	b2Fixture* createFixture(const Shape* shape);
	b2Fixture* createFixture(const b2FixtureDef& fixDef);

private:
	Body();
	Body(b2Body* b2bd, Type tp);
	
	void setBody(b2Body* b2bd);

	b2Body* body;
	Type type;
};

}

#endif