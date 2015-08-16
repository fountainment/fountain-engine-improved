#if !defined(_FEI_RENDEROBJ_H_)
#define _FEI_RENDEROBJ_H_

#include "base/NodeBase.h"

namespace fei {

class RenderObj : public fei::NodeBase
{
public:
	virtual void draw();
protected:
	bool _isAlpha;
	int alphaFunc;
};

}

#endif
