#ifndef _FEI_RENDERTREE_H_
#define _FEI_RENDERTREE_H_

#include "render/RenderList.h"
#include "render/RenderObj.h"

namespace fei {

class RenderTree : public RenderObj
{
public:
	RenderTree();

	void treeInit();
	void treeDestroy();
	void treeUpdate();
	void treeDraw();

	virtual void feiInit() override;
	virtual void feiDestroy() override;
	virtual void feiBasicUpdate() override;

	virtual void drawIt() override;

	void setRoot(RenderObj* rObj);
	void addChild(RenderObj* rObj);
	void delChild(RenderObj* rObj);
	void sort();

private:
	RenderObj* _root;
	RenderList _childList;
};

} // namespace fei

#endif // _FEI_RENDERTREE_H_
