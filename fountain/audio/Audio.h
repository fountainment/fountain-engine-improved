#ifndef _FEI_AUDIO_H_
#define _FEI_AUDIO_H_

//TODO: add a non-conflict audio source class

#include <AL/al.h>
#include <AL/alc.h>

#include "base/ModuleBase.h"
#include "math/Vec2.h"
#include "math/Vec3.h"

namespace fei {

class Audio : public ModuleBase
{
public:
	bool init() override;
	void destroy() override;

	void setListenerPosition(const Vec3& v);
	void setListenerVelocity(const Vec3& v);
	void setListenerOrientation(const Vec3& vec, const Vec3& up);

	void setListenerPosition(const Vec2& v);
	void setListenerVelocity(const Vec2& v);
	void setListenerOrientation(const Vec2& vec);

	void setListenerGain(float gain);

	void setDopplerFactor(float doplerFactor);
	void setSpeedOfSound(float speedOfSound);

	static Audio* getInstance();

private:
	Audio();

	ALCdevice *_audioDevice;
	ALCcontext *_context;

	static Audio *instance_;
};

} // namespace fei

#endif // _FEI_AUDIO_H_
