#include "physics/Physics.h"

#include "math/Circle.h"
#include "math/Polygon.h"
#include "math/Rect.h"
#include "render/Color.h"
#include "render/Render.h"

using fei::Physics;

class DebugDraw : public b2Draw
{
public:
	~DebugDraw()
	{
	}

	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		fei::Color(color.r, color.g, color.b).use();
		fei::Polygon polygon;
		polygon.setVertices(vertexCount, (float*)&(vertices[0].x));
		polygon.zoom(fei::Physics::getInstance()->getRatio());
		polygon.setSolid(false);
		fei::Render::drawShape(&polygon);
	}

	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		fei::Color(color.r, color.g, color.b).use();
		fei::Polygon polygon;
		polygon.setVertices(vertexCount, (float*)&(vertices[0].x));
		polygon.zoom(fei::Physics::getInstance()->getRatio());
		fei::Render::drawShape(&polygon);
		fei::Color(color.r + 0.2f, color.g + 0.2f, color.b + 0.2f).use();
		polygon.setSolid(false);
		fei::Render::drawShape(&polygon);
	}

	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
	{
		fei::Color(color.r, color.g, color.b).use();
		fei::Circle circle(Physics::getInstance()->physicsToRender(radius));
		circle.setPosition(Physics::getInstance()->physicsToRender(fei::Vec2(center.x, center.y)));
		circle.setSolid(false);
		fei::Render::drawShape(&circle);
	}

	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
	{
		fei::Color(color.r, color.g, color.b).use();
		fei::Circle circle(Physics::getInstance()->physicsToRender(radius));
		circle.setPosition(Physics::getInstance()->physicsToRender(fei::Vec2(center.x, center.y)));
		fei::Render::drawShape(&circle);
		fei::Color::White.use();
		DrawSegment(center, center + radius * axis, b2Color(1.0f, 1.0f, 1.0f));
		DrawCircle(center, radius, b2Color(color.r + 0.2f, color.g + 0.2f, color.b + 0.2f));
	}

	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
		fei::Vec2 a(p1.x, p1.y);
		fei::Vec2 b(p2.x, p2.y);
		a = Physics::getInstance()->physicsToRender(a);
		b = Physics::getInstance()->physicsToRender(b);
		fei::Color(color.r, color.g, color.b).use();
		//Render::getInstance()->drawSegment(a, b);
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

	void DrawParticles(const b2Vec2 *, float32, const b2ParticleColor *, int32)
	{
		//TODO implement DebugDraw::DrawParticles
	}
};

Physics* Physics::instance = nullptr;

Physics* Physics::getInstance()
{
	if (!instance) {
		instance = new Physics();
	}
	return instance;
}

Physics::Physics()
: world(nullptr),
  debugDraw(nullptr),
  ddCamera(nullptr),
  doDebugDraw(false),
  ratio(1.0f)
{
}

bool Physics::init()
{
	b2Vec2 g(0.0f, -10.0f);
	world = new b2World(g);
	debugDraw = new DebugDraw;
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	//flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	//flags += b2Draw::e_centerOfMassBit;
	debugDraw->SetFlags(flags);
	world->SetAllowSleeping(true);
	world->SetDebugDraw(debugDraw);
	return true;
}

void Physics::destroy()
{
	delete world;
	world = nullptr;
}

void Physics::executeBeforeFrame()
{
	world->Step(0.0167f, 8, 3);
}

void Physics::executeAfterFrame()
{
	if (doDebugDraw) {
		if (ddCamera) {
			ddCamera->update();
		}
		world->DrawDebugData();
	}
}

void Physics::setGravity(const fei::Vec2& g)
{
	world->SetGravity(b2Vec2(g.x, g.y));
}

const fei::Vec2 Physics::getGravity()
{
	auto g = world->GetGravity();
	return fei::Vec2(g.x, g.y);
}

void Physics::setRatio(float rt)
{
	ratio = rt;
}

float Physics::getRatio()
{
	return ratio;
}

fei::Body* Physics::createBody(const fei::Vec2& pos, fei::Body::Type type)
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
	auto b2bd = world->CreateBody(&bodyDef);
	auto body = new Body(b2bd, type);
	return body;
}

void Physics::destroyBody(fei::Body* body)
{
	world->DestroyBody(body->body);
	delete body;
}

void Physics::setDoDebugDraw(bool doDD)
{
	doDebugDraw = doDD;
}

void Physics::setDebugDrawCamera(fei::Camera* cam)
{
	ddCamera = cam;
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
			auto pos = shape->getPosition();
			b2Vec2 vec[2];
			vec[0] = b2Vec2(data[0] + pos.x, data[1] + pos.y);
			vec[1] = b2Vec2(data[2] + pos.x, data[3] + pos.y);
			lShape->CreateChain(vec, shape->getDataSize());
			b2shape = lShape;
		}
		break;
	}
	return b2shape;
}
