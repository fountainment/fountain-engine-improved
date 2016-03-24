#include "physics/FixtureGroup.h"

using fei::FixtureGroup;

FixtureGroup::FixtureGroup()
{
}

FixtureGroup::FixtureGroup(const std::vector<b2Fixture*>& fixtures)
{
	clone(fixtures);
}

FixtureGroup::FixtureGroup(b2Fixture* fixture)
{
	clone(fixture);
}

void FixtureGroup::operator=(const std::vector<b2Fixture*>& fixtures)
{
	clone(fixtures);
}

void FixtureGroup::operator=(b2Fixture* fixture)
{
	clone(fixture);
}

void FixtureGroup::setSensor(bool flag)
{
	for (auto fixture : _fixtures) {
		fixture->SetSensor(flag);
	}
}

void FixtureGroup::setMaskBits(int mask)
{
	for (auto fixture : _fixtures) {
		auto data = fixture->GetFilterData();
		data.maskBits = mask;
		fixture->SetFilterData(data);
	}
}

void FixtureGroup::setGroupIndex(int index)
{
	for (auto fixture : _fixtures) {
		auto data = fixture->GetFilterData();
		data.groupIndex = index;
		fixture->SetFilterData(data);
	}
}

void FixtureGroup::clone(const std::vector<b2Fixture*>& fixtures)
{
	_fixtures = fixtures;
}

void FixtureGroup::clone(b2Fixture* fixture)
{
	_fixtures.clear();
	_fixtures.push_back(fixture);
}
