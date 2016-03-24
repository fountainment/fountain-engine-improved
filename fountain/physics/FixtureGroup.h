#ifndef _FEI_FIXTURE_GROUP_H_
#define _FEI_FIXTURE_GROUP_H_

//TODO: test FixtureGroup

#include <Box2D/Box2D.h>

#include "base/basedef.h"

namespace fei {

class FixtureGroup
{
public:
	FixtureGroup();
	FixtureGroup(const std::vector<b2Fixture*>& fixtures);
	FixtureGroup(b2Fixture* fixture);

	void operator=(const std::vector<b2Fixture*>& fixtures);
	void operator=(b2Fixture* fixture);

	void setSensor(bool flag);
	void setMaskBits(int mask);
	void setGroupIndex(int index);

	std::vector<b2Fixture*> _fixtures;

private:
	void clone(const std::vector<b2Fixture*>& fixtures);
	void clone(b2Fixture* fixture);
};

} // namespace fei

#endif // _FEI_FIXTURE_GROUP_H_
