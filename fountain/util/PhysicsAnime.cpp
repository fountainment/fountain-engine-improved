#include "PhysicsAnime.h"

using fut::CollisionFrameAnime;

CollisionFrameAnime::CollisionFrameAnime()
: _body(nullptr),
  _oldFrameIndex(-1)
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

void CollisionFrameAnime::setFrameMap(const std::map<int, std::vector<fei::Polygon>> frameMap)
{
	_frameMap = frameMap;
}

void CollisionFrameAnime::deleteFrame(int frameIndex)
{
	auto frame = _frameMap.find(frameIndex);
	if (frame != _frameMap.end()) {
		_frameMap.erase(frame);
	}
}

void CollisionFrameAnime::update(fei::RenderObj* rObj)
{
	int cfi = getCurFrameIndex();
	if (_oldFrameIndex != cfi) {
		auto frame = _frameMap.find(cfi);
		if (cfi < _oldFrameIndex) {
			destroyFixture();
		}
		if (frame != _frameMap.end()) {
			destroyFixture();
			createFixture(frame->second);
		}
		_oldFrameIndex = cfi;
	}
}

void CollisionFrameAnime::print()
{
	for (auto& frame : _frameMap) {
		std::printf("%d\n", frame.first);
		std::printf("%d\n", (int)frame.second.size());
		for (auto& poly : frame.second) {
			poly.print();
		}
	}
}

void CollisionFrameAnime::destroyFixture()
{
	if (_body) {
		_body->destroyFixture(_fixture.fixtures);
	}
	_fixture.fixtures.clear();
}

void CollisionFrameAnime::createFixture(const std::vector<fei::Polygon>& polyVec)
{
	if (_body) {
		_fixture = _body->createFixture(polyVec);
	}
}
