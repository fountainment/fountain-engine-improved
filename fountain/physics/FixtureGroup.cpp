#include "physics/FixtureGroup.h"

using fei::FixtureGroup;

FixtureGroup::FixtureGroup()
{
}

FixtureGroup::FixtureGroup(const std::vector<b2Fixture*>& _fixtures)
{
	clone(_fixtures);
}

FixtureGroup::FixtureGroup(b2Fixture* _fixture)
{
	clone(_fixture);
}

void FixtureGroup::operator=(const std::vector<b2Fixture*>& _fixtures)
{
	clone(_fixtures);
}

void FixtureGroup::operator=(b2Fixture* _fixture)
{
	clone(_fixture);
}

void FixtureGroup::setSensor(bool flag)
{
	for (auto fixture : fixtures) {
		fixture->SetSensor(flag);
	}
}

void FixtureGroup::setMaskBits(int mask)
{
	for (auto fixture : fixtures) {
		auto data = fixture->GetFilterData();
		data.maskBits = mask;
		fixture->SetFilterData(data);
	}
}

void FixtureGroup::setGroupIndex(int index)
{
	for (auto fixture : fixtures) {
		auto data = fixture->GetFilterData();
		data.groupIndex = index;
		fixture->SetFilterData(data);
	}
}

void FixtureGroup::clone(const std::vector<b2Fixture*>& _fixtures)
{
	fixtures = _fixtures;
}

void FixtureGroup::clone(b2Fixture* _fixture)
{
	fixtures.clear();
	fixtures.push_back(_fixture);
}
