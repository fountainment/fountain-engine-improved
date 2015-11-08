#include "PhysicsAnime.h"

using fut::CollisionFrameAnime;

CollisionFrameAnime::CollisionFrameAnime()
: _body(nullptr),
  _oldFrameIndex(0)
{
}

CollisionFrameAnime::~CollisionFrameAnime()
{
	destroyFixture();
}

void CollisionFrameAnime::setBody(fei::Body* body)
{
	_body = body;
}

void CollisionFrameAnime::insertFrame(int frameIndex, const fei::Polygon& poly)
{
	_frameMap[frameIndex] = poly.box2dDecomposition();
}

void CollisionFrameAnime::insertFrame(const std::map<int, const fei::Polygon>& frames)
{
	for (auto frame : frames) {
		insertFrame(frame.first, frame.second);
	}
}

void CollisionFrameAnime::update(fei::RenderObj* rObj)
{
	int cfi = getCurFrameIndex();
	std::printf("%d\n", cfi);
	if (_oldFrameIndex != cfi) {
		auto frame = _frameMap.find(cfi);
		if (frame != _frameMap.end()) {
			destroyFixture();
			std::printf("%d!!!!\n", cfi);
			createFixture(frame->second);
		}
		_oldFrameIndex = cfi;
	}
}

void CollisionFrameAnime::destroyFixture()
{
	if (_body) {
		_body->destroyFixture(_fixture.fixtures);
		_fixture.fixtures.clear();
	}
}

void CollisionFrameAnime::createFixture(const std::vector<fei::Polygon>& polyVec)
{
	if (_body) {
		_fixture = _body->createFixture(polyVec);
	}
}
