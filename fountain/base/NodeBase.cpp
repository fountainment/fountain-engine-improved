#include "base/NodeBase.h"

using fei::NodeBase;

void NodeBase::init()
{
}

void NodeBase::destroy()
{
}

void NodeBase::update()
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
	update();
}

