#include "ModuleBase.h"

using fei::ModuleBase;

ModuleBase::ModuleBase()
{
	_isLoad = false;
}

ModuleBase::~ModuleBase()
{
}

bool ModuleBase::init()
{
	_isLoad = true;
	return _isLoad;
}

void ModuleBase::executeBeforeFrame()
{
}

void ModuleBase::executeAfterFrame()
{
}

void ModuleBase::destroy()
{
	_isLoad = false;
}

bool ModuleBase::isLoad()
{
	return _isLoad;
}
