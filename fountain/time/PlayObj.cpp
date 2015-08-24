#include "PlayObj.h"

using fei::PlayObj;

PlayObj::PlayObj()
: _isLoop(false)
{	
}

bool PlayObj::isLoop()
{
	return _isLoop;
}

void PlayObj::setLoop(bool loop)
{
	_isLoop = loop;
}