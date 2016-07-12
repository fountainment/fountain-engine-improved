#include "TestScene.h"

#include "fountain.h"

using namespace fei;

void TestObj::update()
{
	auto seg = getSegmentPtr();
	auto vec = seg->getVector() * 0.5f;
	seg->a = getPosition() + vec;
	seg->b = getPosition() - vec;

}

const fei::Segment TestObj::getSegment()
{
	return _seg;
}

fei::Segment* TestObj::getSegmentPtr()
{
	return &_seg;
}

void TopoScene::init()
{
	setCamera(&_cam);
	_cam.setCameraSize(Interface::getInstance()->getCurrentWindow()->getFrameSize());
	_char = new TestObj(Segment(Vec2(-25.0f, 0.0f), Vec2(25.0f, 0.0f)));
	_char->setAnchor(Vec2(0.0f, -25.0f));

	_char->load("res/image/topo/char.png");
	add(_char);

	TestObj* wall;
	auto posVec = {Vec2::ZERO, Vec2(10.0f, 50.0f)};
	for (auto pos : posVec) {
		wall = new TestObj(Segment(Vec2(-100.0f, -45.0f), Vec2(100.0f, 45.0f)));
		wall->setAnchor(Vec2(0.0f, -55.0f));
		wall->load("res/image/topo/wall.png");
		wall->setPosition(pos);

		add(wall);
	}
}

void TopoScene::destroy()
{
	throwAwayAll();
}

void TopoScene::update()
{
	auto axis = Interface::getInstance()->getCurrentWindow()->getKeyAxis();
	_char->move(axis);

	topoSort();
	std::printf("%f\n", fei::Time::getInstance()->getFps());	
}

std::vector<Segment> TopoScene::getSegments()
{
	std::vector<Segment> ret;
	auto vec = getListVector();
	for (auto i : vec) {
		ret.push_back(static_cast<TestObj*>(i)->getSegment());
	}
	return ret;
}

void TopoScene::topoSort()
{
	auto segs = getSegments();
	int segNum = segs.size();
	std::vector<int> result;
	std::vector<std::vector<int>> graph(1000);
	std::vector<int> ind(1000);
	for (int i = 0; i < segNum; i++) {
		ind[i] = 0;
	}
	for (int i = 0; i < segNum - 1; i++) {
		for (int j = i + 1; j < segNum; j++) {
			auto t = segs[i].cmpRenderY(segs[j]);
			if (t != 0) {
				if (t > 0) {
					ind[j]++;
					graph[i].push_back(j);
				} else {
					ind[i]++;
					graph[j].push_back(i);
				}
			}
		}
	}
	std::queue<int> z;
	for (int i = 0; i < segNum; i++) {
		if (ind[i] == 0) {
			z.push(i);
		}
	}
	while (!z.empty()) {
		int t = z.front();
		result.push_back(t);
		z.pop();
		for (auto i : graph[t]) {
			ind[i]--;
			if (ind[i] == 0) {
				z.push(i);
			}
		}
	}
	listRearrange(result);
}
