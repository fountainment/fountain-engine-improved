#include "physics/Physics.h"

#include "math/Circle.h"
#include "math/Polygon.h"
#include "math/Rect.h"
#include "render/Color.h"
#include "render/Render.h"
#include "render/ShapeObj.h"
#include "time/Time.h"

using fei::Physics;
using fei::ContactInfo;
using fei::ContactListener;

class DebugDraw : public b2Draw
{
public:
	DebugDraw()
	{
		_shapeObj.setHasAlpha(true);
	}

	~DebugDraw()
	{
	}

	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		_polygon.setVertices(vertexCount, (float*)&(vertices[0].x));
		_polygon.zoom(fei::Physics::getInstance()->getRatio());
		_polygon.setSolid(false);
		_shapeObj.setColor(fei::Color(color.r, color.g, color.b));
		_shapeObj.setShape(&_polygon);
		_shapeObj.draw();
	}

	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		_polygon.setVertices(vertexCount, (float*)&(vertices[0].x));
		_polygon.zoom(fei::Physics::getInstance()->getRatio());
		_polygon.setSolid(true);
		_shapeObj.setColor(fei::Color(color.r, color.g, color.b, 0.5f));
		_shapeObj.setShape(&_polygon);
		_shapeObj.draw();
		DrawPolygon(vertices, vertexCount, b2Color(color.r + 0.2f, color.g + 0.2f, color.b + 0.2f));
	}

	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
	{
		_circle.setRadius(Physics::getInstance()->physicsToRender(radius));
		_circle.setPosition(Physics::getInstance()->physicsToRender(fei::Vec2(center.x, center.y)));
		_circle.setSolid(false);
		_shapeObj.setColor(fei::Color(color.r, color.g, color.b));
		_shapeObj.setShape(&_circle);
		_shapeObj.draw();
	}

	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
	{
		_circle.setRadius(Physics::getInstance()->physicsToRender(radius));
		_circle.setPosition(Physics::getInstance()->physicsToRender(fei::Vec2(center.x, center.y)));
		_circle.setSolid(true);
		_shapeObj.setColor(fei::Color(color.r, color.g, color.b, 0.5f));
		_shapeObj.setShape(&_circle);
		_shapeObj.draw();
		auto lineColor = b2Color(color.r + 0.2f, color.g + 0.2f, color.b + 0.2f);
		DrawSegment(center, center + radius * axis, lineColor);
		DrawCircle(center, radius, lineColor);
	}

	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
		fei::Vec2 a(p1.x, p1.y);
		fei::Vec2 b(p2.x, p2.y);
		a = Physics::getInstance()->physicsToRender(a);
		b = Physics::getInstance()->physicsToRender(b);
		_segment.a = a;
		_segment.b = b;
		_shapeObj.setColor(fei::Color(color.r, color.g, color.b));
		_shapeObj.setShape(&_segment);
		_shapeObj.draw();
	}

	void DrawTransform(const b2Transform& xf)
	{
		b2Vec2 p1 = xf.p, p2;
		const float32 k_axisScale = 0.2f;
		p2 = p1 + k_axisScale * xf.q.GetXAxis();
		DrawSegment(p1, p2, b2Color(1.0f, 0.0f, 0.0f));

		p2 = p1 + k_axisScale * xf.q.GetYAxis();
		DrawSegment(p1, p2, b2Color(0.0f, 1.0f, 0.0f));
	}

	void DrawParticles(const b2Vec2* centers, float32 radius, const b2ParticleColor* colors, int32 count)
	{
		_shapeObj.setShape(&_circle);
		_circle.setRadius(Physics::getInstance()->physicsToRender(radius));
		_circle.setSolid(true);
		for (int32 i = 0; i < count; i++) {
			auto pos = Physics::getInstance()->physicsToRender(fei::Vec2(centers[i].x, centers[i].y));
			_circle.setPosition(pos);
			_shapeObj.setColor(fei::Color(colors[i].r, colors[i].g, colors[i].b, 0.5f));
			_shapeObj.draw();
		}
	}

private:
	fei::ShapeObj _shapeObj;
	fei::Polygon _polygon;
	fei::Circle _circle;
	fei::Segment _segment;
};


ContactInfo ContactListener::contactInfo_;

void ContactListener::BeginContact(b2Contact* contact)
{
	updateContactInfo(contact);
	auto fixtureA = contact->GetFixtureA();
	auto fixtureB = contact->GetFixtureB();
	auto feiBodyA = Physics::getBodyByB2Fixture(fixtureA);
	auto feiBodyB = Physics::getBodyByB2Fixture(fixtureB);
	if (!feiBodyA || !feiBodyB) return;

	contactInfo_.valid = !fixtureA->IsSensor() && !fixtureB->IsSensor();
	contactInfo_.setFixture(fixtureA, fixtureB);
	feiBodyA->beginContact(feiBodyB);

	contactInfo_.setFixture(fixtureB, fixtureA);
	contactInfo_.normal *= -1.0f;
	feiBodyB->beginContact(feiBodyA);
}

void ContactListener::EndContact(b2Contact* contact)
{
	auto fixtureA = contact->GetFixtureA();
	auto fixtureB = contact->GetFixtureB();
	auto feiBodyA = Physics::getBodyByB2Fixture(fixtureA);
	auto feiBodyB = Physics::getBodyByB2Fixture(fixtureB);
	if (!feiBodyA || !feiBodyB) return;

	contactInfo_.valid = false;
	contactInfo_.setFixture(fixtureA, fixtureB);
	feiBodyA->endContact(feiBodyB);

	contactInfo_.setFixture(fixtureB, fixtureA);
	feiBodyB->endContact(feiBodyA);
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	updateContactInfo(contact);
	auto fixtureA = contact->GetFixtureA();
	auto fixtureB = contact->GetFixtureB();
	auto feiBodyA = Physics::getBodyByB2Fixture(fixtureA);
	auto feiBodyB = Physics::getBodyByB2Fixture(fixtureB);
	if (!feiBodyA || !feiBodyB) return;

	contactInfo_.valid = true;
	contactInfo_.setFixture(fixtureA, fixtureB);
	bool isContactABEnabled = feiBodyA->frameContact(feiBodyB);

	contactInfo_.setFixture(fixtureB, fixtureA);
	contactInfo_.normal *= -1.0f;
	bool isContactBAEnabled = feiBodyB->frameContact(feiBodyA);
	if (!isContactABEnabled || !isContactBAEnabled) {
		contact->SetEnabled(false);
	}
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	//TODO: implement ContactListener::PostSolve
}

void ContactListener::updateContactInfo(b2Contact* contact)
{
	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);
	b2Vec2 normal = (worldManifold.normal);
	b2Vec2 point = worldManifold.points[0];
	contactInfo_.normal = fei::Vec2(normal.x, normal.y);
	contactInfo_.collidePoint = fei::Vec2(point.x, point.y);
}

ContactInfo* ContactListener::getContactInfo()
{
	return &contactInfo_;
}


Physics* Physics::instance_ = nullptr;

Physics* Physics::getInstance()
{
	if (!instance_) {
		instance_ = new Physics();
	}
	return instance_;
}

Physics::Physics()
: _world(nullptr),
  _debugDraw(nullptr),
  _contactListener(nullptr),
  _ddCamera(nullptr),
  _doDebugDraw(false),
  _inStep(false),
  _ratio(1.0f)
{
}

bool Physics::init()
{
	b2Vec2 g(0.0f, -10.0f);
	_world = new b2World(g);
	_debugDraw = new DebugDraw;
	_contactListener = new ContactListener;
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	//flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_particleBit;
	//flags += b2Draw::e_centerOfMassBit;
	_debugDraw->SetFlags(flags);
	_world->SetAllowSleeping(true);
	_world->SetDebugDraw(_debugDraw);
	_world->SetContactListener(_contactListener);
	return true;
}

void Physics::destroy()
{
	delete _world;
	delete _contactListener;
	delete _debugDraw;
	_world = nullptr;
	_contactListener = nullptr;
	_debugDraw = nullptr;
}

void Physics::executeBeforeFrame()
{
	_inStep = true;
	float deltaTime = static_cast<float>(fei::Time::getInstance()->getDeltaTime());
	_world->Step(deltaTime, 8, 3);
	_inStep = false;
	_world->ClearForces();

	while (!_afterStepProcessQueue.empty()) {
		auto func = _afterStepProcessQueue.front();
		_afterStepProcessQueue.pop();
		func();
	}
}

void Physics::executeAfterFrame()
{
	if (_doDebugDraw) {
		if (_ddCamera) {
			_ddCamera->update();
		}
		_world->DrawDebugData();
	}
}

void Physics::setGravity(const fei::Vec2& g)
{
	_world->SetGravity(b2Vec2(g.x, g.y));
	wakeUpAllBodies();
}

const fei::Vec2 Physics::getGravity()
{
	auto g = _world->GetGravity();
	return fei::Vec2(g.x, g.y);
}

void Physics::setRatio(float rt)
{
	_ratio = rt;
}

void Physics::wakeUpAllBodies()
{
	for (auto b = _world->GetBodyList(); b; b = b->GetNext()) {
		b->SetAwake(true);
	}
}

fei::Body* fei::Physics::createBody(const fei::Vec2& pos, fei::Body::Type type)
{
	b2BodyDef bodyDef;
	auto physicsPos = renderToPhysics(pos);
	bodyDef.position.Set(physicsPos.x, physicsPos.y);
	switch(type) {
	case fei::Body::Type::STATIC:
		bodyDef.type = b2_staticBody;
		break;
	case fei::Body::Type::DYNAMIC:
		bodyDef.type = b2_dynamicBody;
		break;
	case fei::Body::Type::KINEMATIC:
		bodyDef.type = b2_kinematicBody;
		break;
	}
	auto b2bd = _world->CreateBody(&bodyDef);
	return new Body(b2bd, type);
}

void Physics::destroyBody(fei::Body* body)
{
	if (body->_destroyed) {
		return;
	}
	body->getB2Body()->SetUserData(nullptr);
	if (isInStep()) {
		_afterStepProcessQueue.push(
			[this, body]()
			{
				_world->DestroyBody(body->getB2Body());
				delete body;
			}
		);
		body->_destroyed = true;
		return;
	}
	_world->DestroyBody(body->getB2Body());
	delete body;
}

void Physics::setDoDebugDraw(bool doDD)
{
	_doDebugDraw = doDD;
}

void Physics::setDebugDrawCamera(fei::Camera* cam)
{
	_ddCamera = cam;
}

bool Physics::isInStep()
{
	return _inStep;
}

std::queue<std::function<void()>>* Physics::getAfterStepProcessQueue()
{
	return &_afterStepProcessQueue;
}

b2Shape* Physics::ShapeToB2Shape(const fei::Shape* shape)
{
	b2Shape *b2shape = nullptr;
	auto pos = shape->getPosition();
	pos = Physics::getInstance()->renderToPhysics(pos);
	switch (shape->getType()) {
	case fei::Shape::Type::POLYGON:
		{
			auto pShape = new b2PolygonShape;
			auto array = ((fei::Polygon*)shape)->getDataVector();
			for (auto& vertex : array) {
				vertex = Physics::getInstance()->renderToPhysics(vertex);
				vertex += pos;
			}
			if (!array.empty()) {
				pShape->Set((const b2Vec2*)(&array[0]), shape->getDataSize());
			}
			b2shape = pShape;
		}
		break;
	case fei::Shape::Type::CIRCLE:
		{
			auto cShape = new b2CircleShape;
			cShape->m_p = b2Vec2(pos.x, pos.y);
			cShape->m_radius = Physics::getInstance()->renderToPhysics(((fei::Circle*)shape)->getRadius());
			b2shape = cShape;
		}
		break;
	case fei::Shape::Type::RECT:
		{
			auto pShape = new b2PolygonShape;
			auto size = ((fei::Rect*)shape)->getSize() * 0.5f;
			auto center = ((fei::Rect*)shape)->getCenter();
			size = Physics::getInstance()->renderToPhysics(size);
			center = Physics::getInstance()->renderToPhysics(center);
			pShape->SetAsBox(size.x, size.y, b2Vec2(center.x, center.y), 0.0f);
			b2shape = pShape;
		}
		break;
	case fei::Shape::Type::SEGMENT:
		{
			auto lShape = new b2ChainShape;
			auto data = shape->getDataPtr();
			b2Vec2 vec[2];
			float physicsData[4];
			for (int i = 0; i < 4; i++) {
				physicsData[i] = Physics::getInstance()->renderToPhysics(data[i]);
			}
			vec[0] = b2Vec2(physicsData[0] + pos.x, physicsData[1] + pos.y);
			vec[1] = b2Vec2(physicsData[2] + pos.x, physicsData[3] + pos.y);
			lShape->CreateChain(vec, shape->getDataSize());
			b2shape = lShape;
		}
		break;
	}
	return b2shape;
}
