#if !defined(_FEI_BODY_H_)
#define _FEI_BODY_H_

#include <Box2D/Box2D.h>
#include "math/Vec2.h"

namespace fei {

class Body
{
public:
	friend class Physics;

	enum class Type {
		Static = 1,
		Dynamic = 2,
		Kinematic = 3
	};

private:
	Body();
	Body(b2Body* b2bd, Type tp);
	
	void setBody(b2Body* b2bd);
	const fei::Vec2 getPosition() const;
	float getAngle() const;

	b2Body* body;
	Type type;
};

}

#endif