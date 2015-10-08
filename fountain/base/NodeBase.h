#if !defined(_FEI_NODEBASE_H_)
#define _FEI_NODEBASE_H_

#include "math/Vec2.h"

namespace fei {

class NodeBase
{
protected:
	fei::Vec2 pos;
	bool _isLoaded;

public:
	NodeBase();

	const fei::Vec2 getPosition() const;
	void setPosition(const Vec2& v);
	void move(const Vec2& v);

	bool isLoaded() const;

	virtual void init();
	virtual void destroy();
	virtual void update();

	virtual void feiInit();
	virtual void feiDestroy();
	virtual void feiUpdate();
};

}

inline fei::NodeBase::NodeBase()
: pos(fei::Vec2::ZERO),
  _isLoaded(false)
{
}

inline const fei::Vec2 fei::NodeBase::getPosition() const
{
	return pos;
}

inline void fei::NodeBase::setPosition(const fei::Vec2& v)
{
	pos = v;
}

inline void fei::NodeBase::move(const fei::Vec2& v)
{
	pos.add(v);
}

inline bool fei::NodeBase::isLoaded() const
{
	return _isLoaded;
}

#endif
