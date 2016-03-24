#include "time/PlayObj.h"

#include "time/Time.h"

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

void PlayObj::play()
{
	_playClock.play();
}

void PlayObj::pause()
{
	_playClock.pause();
}

void PlayObj::stop()
{
	_playClock.stop();
}

bool PlayObj::isStop()
{
	return _playClock.isStop();
}

bool PlayObj::isPlay()
{
	return _playClock.isPlay();
}

double PlayObj::getDeltaTime()
{
	return _playClock.getDeltaTime();
}

void PlayObj::setMasterClock(fei::Clock* clock)
{
	_playClock.setMasterClock(clock);
}

