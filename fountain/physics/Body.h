#if !defined(_FEI_BODY_H_)
#define _FEI_BODY_H_

#include <Box2D/Box2D.h>

#include "base/basedef.h"
#include "math/Polygon.h"
#include "math/Shape.h"
#include "math/Vec2.h"

namespace fei {

class Body
{
public:
	friend class ContactListener;
	friend class Physics;

	enum class Type {
		STATIC = 1,
		DYNAMIC = 2,
		KINEMATIC = 3
	};

	const fei::Vec2 getPosition() const;
	float getAngle() const;

	b2Body* getB2Body() const;

	void setSpeed(const Vec2& sp);
	const Vec2 getSpeed();

	void setTag(int tag);
	int getTag();

	b2Fixture* createFixture(const Shape* shape);
	const std::vector<b2Fixture*> createFixture(const std::vector<Shape*>& shapeList);
	const std::vector<b2Fixture*> createFixture(const Polygon& poly);
	const std::vector<b2Fixture*> createFixture(const std::vector<Polygon>& polyList);
	b2Fixture* createFixture(const b2FixtureDef& fixDef);

	void destroyFixture(b2Fixture* fixture);
	void destroyFixture(const std::vector<b2Fixture*>& fixtures);

	void setBeginContactCallback(std::function<void(Body*)> callbackFunc);
	void setFrameContactCallback(std::function<bool(Body*)> callbackFunc);
	void setEndContactCallback(std::function<void(Body*)> callbackFunc);

private:
	Body();
	Body(b2Body* b2bd, Type tp);
	
	void setBody(b2Body* b2bd);

	void beginContact(Body* otherBody);
	bool frameContact(Body* otherBody);
	void endContact(Body* otherBody);

	b2Body* _body;
	Type _type;
	int _tag;
	bool _destroyed;

	std::function<void(Body*)> _beginContactCallback;
	std::function<bool(Body*)> _frameContactCallback;
	std::function<void(Body*)> _endContactCallback;
};

} // namespace fei

#endif // _FEI_BODY_H_
