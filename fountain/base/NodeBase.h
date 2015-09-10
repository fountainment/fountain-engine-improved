#if !defined(_FEI_NODEBASE_H_)
#define _FEI_NODEBASE_H_

#include "math/Vec2.h"

namespace fei {

class NodeBase
{
protected:
	fei::Vec2 pos;	

public:
	const fei::Vec2 getPosition() const;
	void setPosition(const Vec2& v);
	void move(const Vec2& v);
};

}

#endif
