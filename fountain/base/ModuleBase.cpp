#include "ModuleBase.h"

using fei::ModuleBase;

ModuleBase::ModuleBase()
: _isLoad(false)
{
}

ModuleBase::~ModuleBase()
{
}

bool ModuleBase::feiInit()
{
	if (_isLoad) return true;
	_isLoad = init();
	return _isLoad;
}

bool ModuleBase::init()
{
	return true;
}

void ModuleBase::executeBeforeFrame()
{
}

void ModuleBase::executeAfterFrame()
{
}

void ModuleBase::feiDestroy()
{
	if (!_isLoad) return;
	destroy();
	_isLoad = false;
}

void ModuleBase::destroy()
{
}

bool ModuleBase::isLoad()
{
	return _isLoad;
}
