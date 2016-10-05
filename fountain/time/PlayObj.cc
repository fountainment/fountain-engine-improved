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

void PlayObj::resume()
{
	_playClock.resume();
	afterResume();
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

void PlayObj::setPlayCallback(std::function<void()> callback)
{
	_playCallback = callback;
}

void PlayObj::setPauseCallback(std::function<void()> callback)
{
	_pauseCallback = callback;
}

void PlayObj::setResumeCallback(std::function<void()> callback)
{
	_resumeCallback = callback;
}

void PlayObj::setStopCallback(std::function<void()> callback)
{
	_stopCallback = callback;
}

void PlayObj::setTickCallback(std::function<void()> callback)
{
	getClock()->setTickCallback(callback);
}

void PlayObj::afterPlay()
{
	if (_playCallback) {
		_playCallback();
	}
}

void PlayObj::afterPause()
{
	if (_pauseCallback) {
		_pauseCallback();
	}
}

void PlayObj::afterResume()
{
	if (_stopCallback) {
		_stopCallback();
	}
}

void PlayObj::afterStop()
{
	if (isLoop()) {
		play();
	} else {
		if (_stopCallback) {
			_stopCallback();
		}
	}
}
