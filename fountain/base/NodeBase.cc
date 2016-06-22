#include "base/NodeBase.h"

using fei::NodeBase;

void NodeBase::init()
{
}

void NodeBase::destroy()
{
}

void NodeBase::beforeUpdate()
{
}

void NodeBase::update()
{
}

void NodeBase::afterUpdate()
{
}

void NodeBase::feiInit()
{
	if (_isLoaded) return;
	init();
	_isLoaded = true;
}

void NodeBase::feiDestroy()
{
	if (!_isLoaded) return;
	destroy();
	_isLoaded = false;
}

void NodeBase::feiReinit()
{
	feiDestroy();
	feiInit();
}

void NodeBase::feiUpdate()
{
	if (!isActive()) {
		return;
	}
	beforeUpdate();
	feiBasicUpdate();
	update();
	afterUpdate();
}

void NodeBase::feiBasicUpdate()
{
}
