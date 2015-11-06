#if !defined(_FEI_PHYSICSANIME_H_)
#define _FEI_PHYSICSANIME_H_

#include "anime/FrameAnime.h"
#include "base/basedef.h"
#include "math/Polygon.h"
#include "physics/FixtureGroup.h"

namespace fut {

class CollisionFrameAnime : public fei::FrameAnime
{
private:
	std::map<int, std::vector<fei::Polygon>> _frames;
	fei::FixtureGroup _fixture;
};

} // namespace fut

#endif // _FEI_PHYSICSANIME_H_