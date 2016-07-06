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
	afterPlay();
}

void PlayObj::pause()
{
	_playClock.pause();
	afterPause();
}

void PlayObj::stop()
{
	_playClock.stop();
	afterStop();
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

fei::Clock* PlayObj::getClock()
{
	return &_playClock;
}

void PlayObj::setMasterClock(fei::Clock* clock)
{
	_playClock.setMasterClock(clock);
}

void PlayObj::afterPlay()
{
}

void PlayObj::afterPause()
{
}

void PlayObj::afterStop()
{
}
