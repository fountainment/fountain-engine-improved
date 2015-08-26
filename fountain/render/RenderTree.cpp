#include "RenderTree.h"
#include <GL/glew.h>

using fei::RenderTree;

RenderTree::RenderTree()
: root(nullptr)
{
}

void RenderTree::feiInit()
{
	init();
	if (root) {
		root->feiInit();
	}
	childList.feiInit();
}

void RenderTree::feiDestroy()
{
	childList.feiDestroy();
	if (root) {
		root->feiDestroy();
	}
	destroy();
}

void RenderTree::feiUpdate()
{
	update();
	if (root) {
		root->feiUpdate();
	}
	childList.feiUpdate();
}

void RenderTree::drawIt()
{
	glPushMatrix();
	if (root) {
		root->draw();
	}
	childList.draw();
	glPopMatrix();
}

void RenderTree::setRoot(RenderObj* rObj)
{
	root = rObj;
}

void RenderTree::addChild(RenderObj* rObj)
{
	childList.add(rObj);
}

void RenderTree::delChild(RenderObj* rObj)
{
	childList.del(rObj);
}

void RenderTree::sort()
{
	childList.sort();
}
