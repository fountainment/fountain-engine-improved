_Pragma("once")

#include "base/basedef.h"
#include <Box2D/Box2D.h>

namespace fei {

class FixtureGroup
{
public:
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

}
