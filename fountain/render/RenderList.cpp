#include "RenderList.h"
#include <GL/glew.h>

using fei::RenderList;

void RenderList::update()
{
	alphaList.clear();
	normalList.clear();
	for (auto renderObj : objList) {
		renderObj->update();
		if (renderObj->isAlpha()) {
			alphaList.push_back(renderObj);
		} else {
			normalList.push_back(renderObj);
		}
	}
}

void RenderList::drawIt()
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

void RenderList::add(fei::RenderObj* rObj)
{
	objList.push_back(rObj);
}

void RenderList::del(fei::RenderObj* rObj)
{
	objList.remove(rObj);
}

bool zCmp(fei::RenderObj* a, fei::RenderObj* b)
{
	return a->getZPos() < b->getZPos();
}

void RenderList::sort(bool (*cmp)(fei::RenderObj*, fei::RenderObj*) = zCmp)
{
	objList.sort(cmp);
}
