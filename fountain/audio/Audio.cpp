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
	std::printf("OpenAL Version: %s\n", alGetString(AL_VERSION));
	setListenerPosition(fei::Vec2::ZERO);
	setListenerVelocity(fei::Vec2::ZERO);
	setListenerGain(1.0f);
	setListenerOrientation(fei::Vec2::UP);
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

void Audio::setListenerPosition(const fei::Vec3& v)
{
	alListenerfv(AL_POSITION, &v.x);
}

void Audio::setListenerVelocity(const fei::Vec3& v)
{
	alListenerfv(AL_VELOCITY, &v.x);
}

void Audio::setListenerOrientation(const fei::Vec3& vec, const fei::Vec3& up)
{
	ALfloat orientation[] = {vec.x, vec.y, vec.z, up.x, up.y, up.z};
	alListenerfv(AL_ORIENTATION, orientation);
}

void Audio::setListenerPosition(const fei::Vec2& v)
{
	Vec3 v3(v, 0.0f);
	alListenerfv(AL_POSITION, &v3.x);
}

void Audio::setListenerVelocity(const fei::Vec2& v)
{
	Vec3 v3(v, 0.0f);
	alListenerfv(AL_VELOCITY, &v3.x);
}

void Audio::setListenerOrientation(const fei::Vec2& vec)
{
	Vec3 v3Vec(vec, 0.0f), v3Up(0.0f, 0.0f, 1.0f);
	setListenerOrientation(v3Vec, v3Up);
}

void Audio::setListenerGain(float gain)
{
	if (gain < 0.0f || gain > 10.0f) return;
	alListenerf(AL_GAIN, gain);
}

void Audio::setDopplerFactor(float doplerFactor)
{
	alDopplerFactor(doplerFactor);
}

void Audio::setSpeedOfSound(float speedOfSound)
{
	alSpeedOfSound(speedOfSound);
}
