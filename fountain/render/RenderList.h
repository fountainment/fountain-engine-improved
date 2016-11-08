#ifndef _FEI_RENDERLIST_H_
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
	virtual void feiBasicUpdate() override;

	virtual void drawIt() override;

	void add(RenderObj* rObj);
	void del(RenderObj* rObj);
	void clear();
	void throwAway(RenderObj* garbage);
	void throwAwayIf(std::function<bool(RenderObj*)> func);
	void throwAwayAll();

	const std::vector<RenderObj*> getListVector();
	void listRearrange(std::vector<int> newIndex);

	void garbageRecycle();
	void sort(std::function<bool(fei::RenderObj*, fei::RenderObj*)> cmp = RenderListZCmp);
	void topoSort(std::function<int(fei::RenderObj*, fei::RenderObj*)> cmp);

	virtual void processWith(std::function<void(RenderObj*)> func) override;

private:
	std::vector<RenderObj*> _objList;
	std::queue<RenderObj*> _garbageQueue;

	static std::vector<std::vector<int>> dag_;
	static std::vector<int> ind_;
};

} // namespace fei

#endif // _FEI_RENDERLIST_H_
