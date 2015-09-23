#include "ModuleBase.h"

using fei::ModuleBase;

ModuleBase::ModuleBase()
: _isLoaded(false)
{
}

ModuleBase::~ModuleBase()
{
}

bool ModuleBase::feiInit()
{
	if (_isLoaded) return true;
	_isLoaded = init();
	return _isLoaded;
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
	if (!_isLoaded) return;
	destroy();
	_isLoaded = false;
}

void ModuleBase::destroy()
{
}

bool ModuleBase::isLoaded()
{
	return _isLoaded;
}
