#ifndef _FEI_NODEBASE_H_
#define _FEI_NODEBASE_H_

#include "base/basedef.h"
#include "math/Vec2.h"

namespace fei {

class NodeBase
{
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

	const std::string getName() const;
	void setName(const std::string& name);

protected:
	fei::Vec2 _pos;
	bool _isLoaded;
	bool _isActive;
	std::string _name;
};

} // namespace fei

inline fei::NodeBase::NodeBase()
: _pos(fei::Vec2::ZERO),
  _isLoaded(false),
  _isActive(true),
  _name(fei::EmptyStr)
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

inline const std::string fei::NodeBase::getName() const
{
	return _name;
}

inline void fei::NodeBase::setName(const std::string& name)
{
	_name = name;
}
#endif // _FEI_NODEBASE_H_
