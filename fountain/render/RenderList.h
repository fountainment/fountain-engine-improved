#if !defined(_FEI_RENDERLIST_H_)
#define _FEI_RENDERLIST_H_

#include "base/basedef.h"
#include "render/RenderObj.h"

namespace fei {

class RenderList : public fei::RenderObj
{
public:
	virtual void update() override;
	virtual void drawIt() override;

	void add(RenderObj* rObj);
	void del(RenderObj* rObj);

private:
	std::list<RenderObj*> normalList;
	std::list<RenderObj*> alphaList;
};

}

#endif