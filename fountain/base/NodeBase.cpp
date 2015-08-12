#include "base/NodeBase.h"

using fei::NodeBase;

const fei::Vec2 NodeBase::getPosition()
{
	return pos;
}

void NodeBase::setPosition(const fei::Vec2& v)
{
	pos = v;
}

void NodeBase::move(const fei::Vec2& v)
{
	pos.add(v);
}
