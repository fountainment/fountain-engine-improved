#include "TestScene.h"

using namespace fei;

void TestScene::init()
{
	testMath();
	testPhysics();
	testRender();
	testAudio();
}

void TestScene::destroy()
{
}

void TestScene::update()
{
}

void TestScene::testMath()
{
	Vec2 a;
	if (a == Vec2::ZERO) {
		std::printf("Vec2: 1ok!\n");
	}
	a.set(1.5f, 1.5f);
	auto b = a;
	a.mul(10.0f);
	a/=10.0f;
	if (a == b) {
		std::printf("Vec2: 2ok!\n");
	}
	a.add(a);
	if (a == Vec2(3.0f)) {
		std::printf("Vec2: 3ok!\n");
	}
	a = Vec2(10.0f);
	a += a + a * 3.0f / 100.0f;
	if (a == Vec2(20.3f)) {
		std::printf("Vec2: 4ok!\n");
	}
	a.normalize();

	Segment x(Vec2::ZERO, Vec2(10.0f));
	Vec2 tmp;
	if (x.collideRay(tmp, Vec2(10.0f, 0.0f), Vec2(-10.0f, 10.0f))) {
		if (tmp == Vec2(5.0f)) {
			std::printf("Segment: 1ok!\n");
		}
	}

	Polygon y;
	y.pushVertex(Vec2(98.999977, 76.000000));
	y.pushVertex(Vec2(209.999985, 6.999993));
	y.pushVertex(Vec2(141.421356, 141.421356));
	y.pushVertex(Vec2(-141.421356, 141.421356));
	y.pushVertex(Vec2(141.421326, -141.421371));
	y.pushVertex(Vec2(-141.421326, -141.421371));

	auto tl = y.getVisibleVerticesIndex(1);
	std::printf("%lu\n", tl.size());
	for (int vertex : tl) {
		std::printf("%d\n", vertex);
	}
	std::printf("%d\n", y.getBestCutVertexIndex(1));
}

void TestScene::testPhysics()
{
}

void TestScene::testRender()
{

}

void TestScene::testAudio()
{

}
