#include "RenderList.h"
#include <GL/glew.h>

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
	alphaList.clear();
	normalList.clear();
	for (auto renderObj : objList) {
		renderObj->feiUpdate();
		if (renderObj->isAlpha()) {
			alphaList.push_back(renderObj);
		} else {
			normalList.push_back(renderObj);
		}
	}
}

void RenderList::listDraw()
{
	for (auto it = normalList.rbegin(); it != normalList.rend(); ++it) {
		glPushMatrix();
		(*it)->draw();
		glPopMatrix();
	}
	for (auto renderObj : alphaList) {
		glPushMatrix();
		renderObj->draw();
		glPopMatrix();
	}
}

void RenderList::feiInit()
{
	init();
	listInit();
}

void RenderList::feiDestroy()
{
	listDestroy();
	destroy();
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
