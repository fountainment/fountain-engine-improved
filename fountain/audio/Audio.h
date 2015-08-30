#if !defined(_FEI_AUDIO_H_)
#define _FEI_AUDIO_H_

#include "base/ModuleBase.h"
#include <AL/al.h>
#include <AL/alc.h>

namespace fei {

class Audio : public ModuleBase
{
public:
	bool init() override;
	void destroy() override;

	static Audio* getInstance();

private:
	Audio();

	ALCdevice *audioDevice;
	ALCcontext *context;

	static Audio *instance;
};

}

#endif