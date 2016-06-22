#ifndef _FEI_NODEBASE_H_
#define _FEI_NODEBASE_H_

#include "math/Vec2.h"

namespace fei {

class NodeBase
{
protected:
	fei::Vec2 _pos;
	bool _isLoaded;
	bool _isActive;

public:
	NodeBase();

	const fei::Vec2 getPosition() const;
	float getPositionX() const;
	float getPositionY() const;

	void setPosition(const Vec2& v);
	void setPositionX(float x);
	void setPositionY(float y);

	void move(const Vec2& v);

	bool isLoaded() const;

	bool isActive() const;
	void setActive(bool active);

	virtual void init();
	virtual void destroy();
	virtual void beforeUpdate();
	virtual void update();
	virtual void afterUpdate();

	virtual void feiInit();
	virtual void feiDestroy();
	virtual void feiUpdate();
	virtual void feiBasicUpdate();
	void feiReinit();
};

} // namespace fei

inline fei::NodeBase::NodeBase()
: _pos(fei::Vec2::ZERO),
  _isLoaded(false),
  _isActive(true)
{
}

inline const fei::Vec2 fei::NodeBase::getPosition() const
{
	return _pos;
}

inline float fei::NodeBase::getPositionX() const
{
	return _pos.x;
}

inline float fei::NodeBase::getPositionY() const
{
	return _pos.y;
}

inline void fei::NodeBase::setPosition(const fei::Vec2& v)
{
	_pos = v;
}

inline void fei::NodeBase::setPositionX(float x)
{
	_pos.x = x;
}

inline void fei::NodeBase::setPositionY(float y)
{
	_pos.x = y;
}

inline void fei::NodeBase::move(const fei::Vec2& v)
{
	_pos.add(v);
}

inline bool fei::NodeBase::isLoaded() const
{
	return _isLoaded;
}

inline bool fei::NodeBase::isActive() const
{
	return _isActive;
}

inline void fei::NodeBase::setActive(bool active)
{
	_isActive = active;
}
#endif // _FEI_NODEBASE_H_
