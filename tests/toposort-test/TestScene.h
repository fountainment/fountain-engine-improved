#ifndef _TESTSCENE_H_
#define _TESTSCENE_H_

#include "fountain.h"

class TestObj : public fei::Texture
{
public:
	inline TestObj(fei::Segment seg)
	: fei::Texture(),
	  _seg(seg)
	{
		setHasAlpha(true);
	}

	virtual void update() override;

	const fei::Segment getSegment();
	fei::Segment* getSegmentPtr();

private:
	fei::Segment _seg;
};

class TopoScene : public fei::Scene
{
public:
	virtual void init() override;
	virtual void destroy() override;
	virtual void update() override;

private:
	std::vector<fei::Segment> getSegments();
	void topoSort();

	fei::Camera _cam;
	TestObj* _char;
};

#endif // _TESTSCENE_H_
