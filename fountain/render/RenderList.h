#if !defined(_FEI_RENDERLIST_H_)
#define _FEI_RENDERLIST_H_

#include "base/basedef.h"
#include "render/RenderObj.h"

namespace fei {

bool RenderListZCmp(fei::RenderObj* a, fei::RenderObj* b);

class RenderList : public fei::RenderObj
{
public:
	virtual ~RenderList();

	void listInit();
	void listDestroy();
	void listUpdate();
	void listDraw();

	virtual void feiInit() override;
	virtual void feiDestroy() override;
	virtual void feiUpdate() override;

	virtual void drawIt() override;

	void add(RenderObj* rObj);
	void del(RenderObj* rObj);
	void clear();
	void throwAway(RenderObj* garbage);

	std::list<RenderObj*> getListVector();

	void garbageRecycle();
	void sort(bool (*cmp)(fei::RenderObj*, fei::RenderObj*) = RenderListZCmp);

private:
	std::list<RenderObj*> _objList;
	std::queue<RenderObj*> _garbageQueue;
};

} // namespace fei

#endif // _FEI_RENDERLIST_H_
