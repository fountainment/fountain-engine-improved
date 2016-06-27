#ifndef _FEI_PHYSICSSPRITE_H_
#define _FEI_PHYSICSSPRITE_H_

#include "base/basedef.h"
#include "physics/Body.h"
#include "sprite/Sprite.h"

namespace fei {

class PhysicsSprite : public Sprite
{
public:
	PhysicsSprite();
	virtual ~PhysicsSprite();

	void initBody(Body::Type type);
	void destroyBody();

	Body* getBody();

	void physicsSpriteUpdate();

	virtual void feiBasicUpdate();

private:
	Body* _body;
};

} // namespace fei

inline fei::Body* fei::PhysicsSprite::getBody()
{
	return _body;
}

#endif // _FEI_PHYSICSSPRITE_H_
