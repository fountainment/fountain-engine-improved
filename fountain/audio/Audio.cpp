#include "Audio.h"
#include "base/basedef.h"

using fei::Audio;

Audio* Audio::instance = nullptr;

Audio* Audio::getInstance()
{
	if (!instance) {
		instance = new Audio();
	}
	return instance; 
}

Audio::Audio()
{
}

bool Audio::init()
{
	if (_isLoad) return true;
	_isLoad = true;
	audioDevice = alcOpenDevice(nullptr);
	if (!audioDevice) {
		std::fprintf(stderr, "Oops! Sound device not found!\n");
	}
	context = alcCreateContext(audioDevice, nullptr);
	if (!context) {
		std::fprintf(stderr, "Oops! Sound device not found!\n");
	}
	alcMakeContextCurrent(context);
	return _isLoad;
}

void Audio::destroy()
{
	if (!_isLoad) return;
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	alcCloseDevice(audioDevice);
	_isLoad = false;
}