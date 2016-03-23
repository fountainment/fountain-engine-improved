#ifndef _FEI_SOURCE_H_
#define _FEI_SOURCE_H_

#include <AL/al.h>
#include <AL/alc.h>

#include "base/basedef.h"
#include "base/noncopyable.h"
#include "math/Vec2.h"
#include "math/Vec3.h"

namespace fei {

class Source : noncopyable
{
public:
	Source();
	~Source();

	void setPitch(float pitch);
	void setGain(float gain);
	void setVelocity(const Vec2& velocity);
	void setPosition(const Vec2& position);

	bool loadWAV(const std::string& filename);

	void play();
	void pause();
	void stop();
	void setLoop(bool loop);

private:
	ALuint _id;
	ALuint _buffer;
};

} // namespace fei

#endif // _FEI_SOURCE_H_
