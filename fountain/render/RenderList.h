#if !defined(_FEI_RENDERLIST_H_)
#define _FEI_RENDERLIST_H_

#include "base/basedef.h"
#include "render/RenderObj.h"

namespace fei {

bool zCmp(fei::RenderObj* a, fei::RenderObj* b);

class RenderList : public fei::RenderObj
{
public:
	virtual void feiInit() override;
	virtual void feiDestroy() override;
	virtual void feiUpdate() override;

	virtual void drawIt() override;

	void add(RenderObj* rObj);
	void del(RenderObj* rObj);

	void sort(bool (*cmp)(fei::RenderObj*, fei::RenderObj*) = zCmp);

private:
	std::list<RenderObj*> objList;
	std::list<RenderObj*> normalList;
	std::list<RenderObj*> alphaList;
};

}

#endif
