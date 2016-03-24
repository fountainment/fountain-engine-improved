#ifndef _FUT_PHYSICSANIME_H_
#define _FUT_PHYSICSANIME_H_

#include "anime/FrameAnime.h"
#include "base/basedef.h"
#include "math/Polygon.h"
#include "physics/Body.h"
#include "physics/FixtureGroup.h"
#include "physics/Physics.h"
#include "render/RenderObj.h"

namespace fut {

class CollisionFrameAnime : public fei::FrameAnime
{
public:
	CollisionFrameAnime();
	~CollisionFrameAnime();

	void setBody(fei::Body* body);

	void insertFrame(int frameIndex, const fei::Polygon& poly);
	void insertFrame(const std::map<int, const fei::Polygon>& frames);
	void setFrameMap(const std::map<int, std::vector<fei::Polygon>> frameMap);

	void deleteFrame(int frameIndex);

	virtual void update(fei::RenderObj* rObj) override;

	void loadCollisionFile(const std::string& filename);

	void print();

	void destroyFixture();

private:
	void createFixture(const std::vector<fei::Polygon>& polyVec);

	std::map<int, std::vector<fei::Polygon>> _frameMap;
	fei::FixtureGroup _fixture;
	fei::Body* _body;
	int _oldFrameIndex;
};

} // namespace fut

#endif // _FUT_PHYSICSANIME_H_
