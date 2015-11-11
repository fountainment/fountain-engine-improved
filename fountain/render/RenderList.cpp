#include "render/RenderList.h"

#include "render/Render.h"

using fei::RenderList;

void RenderList::listInit()
{
	for (auto renderObj : objList) {
		renderObj->feiInit();
	}
}

void RenderList::listDestroy()
{
	for (auto it = objList.rbegin(); it != objList.rend(); ++it) {
		(*it)->feiDestroy();
	}
}

void RenderList::listUpdate()
{
	for (auto renderObj : objList) {
		renderObj->feiUpdate();
	}
}

void RenderList::listDraw()
{
	for (auto it = objList.rbegin(); it != objList.rend(); ++it) {
		if (!(*it)->hasAlpha()) {
			fei::Render::IndependentDraw(*it);
		}
	}
	for (auto renderObj : objList) {
		if (renderObj->hasAlpha()) {
			fei::Render::IndependentDraw(renderObj);
		}
	}
}

void RenderList::feiInit()
{
	if (_isLoaded) return;
	init();
	listInit();
	_isLoaded = true;
}

void RenderList::feiDestroy()
{
	if (!_isLoaded) return;
	listDestroy();
	destroy();
	_isLoaded = false;
}

void RenderList::feiUpdate()
{
	update();
	listUpdate();
}

void RenderList::drawIt()
{
	listDraw();
}

void RenderList::add(fei::RenderObj* rObj)
{
	if (_isLoaded) {
		rObj->feiInit();
	}
	objList.push_back(rObj);
}

void RenderList::del(fei::RenderObj* rObj)
{
	objList.remove(rObj);
}

void RenderList::sort(bool (*cmp)(fei::RenderObj*, fei::RenderObj*))
{
	objList.sort(cmp);
}

bool RenderListzCmp(fei::RenderObj* a, fei::RenderObj* b)
{
	return a->getZPos() < b->getZPos();
}
