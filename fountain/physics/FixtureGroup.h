#if !defined(_FEI_FIXTURE_GROUP_H_)
#define _FEI_FIXTURE_GROUP_H_

//TODO: test FixtureGroup

#include <Box2D/Box2D.h>

#include "base/basedef.h"

namespace fei {

class FixtureGroup
{
public:
	FixtureGroup();
	FixtureGroup(const std::vector<b2Fixture*>& _fixtures);
	FixtureGroup(b2Fixture* _fixture);

	void operator=(const std::vector<b2Fixture*>& _fixtures);
	void operator=(b2Fixture* _fixture);

	void setSensor(bool flag);
	void setMaskBits(int mask);
	void setGroupIndex(int index);

	std::vector<b2Fixture*> fixtures;

private:
	void clone(const std::vector<b2Fixture*>& _fixtures);
	void clone(b2Fixture* _fixture);
};

} // namespace fei

#endif // _FEI_FIXTURE_GROUP_H_
