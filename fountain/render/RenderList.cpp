#include "RenderList.h"
#include <GL/glew.h>

using fei::RenderList;

void RenderList::update()
{
	for (auto renderObj : normalList) {
		renderObj->update();
	}
	
	for (auto renderObj : alphaList) {
		renderObj->update();
	}
}

void RenderList::drawIt()
{
	glEnable(GL_DEPTH_TEST);
	for (auto it = normalList.rbegin(); it != normalList.rend(); ++it) {
		glPushMatrix();
		(*it)->draw();
		glPopMatrix();
	}
	glDisable(GL_DEPTH_TEST);
	for (auto renderObj : alphaList) {
		glPushMatrix();
		renderObj->draw();
		glPopMatrix();
	}
}

void RenderList::add(fei::RenderObj* rObj)
{
	if (rObj->isAlpha()) {
		alphaList.push_back(rObj);
	} else {
		normalList.push_back(rObj);
	}
}

void RenderList::del(fei::RenderObj* rObj)
{
	normalList.remove(rObj);
	alphaList.remove(rObj);
}