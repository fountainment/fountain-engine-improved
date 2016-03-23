#ifndef _FEI_NODEBASE_H_
#define _FEI_NODEBASE_H_

#include "math/Vec2.h"

namespace fei {

class NodeBase
{
protected:
	fei::Vec2 _pos;
	bool _isLoaded;

public:
	NodeBase();

	const fei::Vec2 getPosition() const;
	void setPosition(const Vec2& v);
	void move(const Vec2& v);

	bool isLoaded() const;

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
  _isLoaded(false)
{
}

inline const fei::Vec2 fei::NodeBase::getPosition() const
{
	return _pos;
}

inline void fei::NodeBase::setPosition(const fei::Vec2& v)
{
	_pos = v;
}

inline void fei::NodeBase::move(const fei::Vec2& v)
{
	_pos.add(v);
}

inline bool fei::NodeBase::isLoaded() const
{
	return _isLoaded;
}

#endif // _FEI_NODEBASE_H_
