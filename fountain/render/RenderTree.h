#if !defined(_FEI_RENDERTREE_H_)
#define _FEI_RENDERTREE_H_

#include "render/RenderObj.h"
#include "render/RenderList.h"

namespace fei {

class RenderTree : public RenderObj
{
public:
	RenderTree();

	virtual void update();
	virtual void drawIt();

	void setRoot(RenderObj* rObj);
	void addChild(RenderObj* rObj);
	void delChild(RenderObj* rObj);

private:
	RenderObj* root;
	RenderList childList;
};

}

#endif