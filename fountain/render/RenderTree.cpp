#include "RenderTree.h"
#include <GL/glew.h>

using fei::RenderTree;

RenderTree::RenderTree()
: root(nullptr)
{
}

void RenderTree::treeInit()
{
	if (root) {
		root->feiInit();
	}
	childList.feiInit();
}

void RenderTree::treeDestroy()
{
	childList.feiDestroy();
	if (root) {
		root->feiDestroy();
	}
}

void RenderTree::treeUpdate()
{
	if (root) {
		root->feiUpdate();
	}
	childList.feiUpdate();
}

void RenderTree::treeDraw()
{
	glPushMatrix();
	if (root) {
		root->draw();
	}
	childList.draw();
	glPopMatrix();
}

void RenderTree::feiInit()
{
	init();
	treeInit();
}

void RenderTree::feiDestroy()
{
	treeDestroy();
	destroy();
}

void RenderTree::feiUpdate()
{
	update();
	treeUpdate();
}

void RenderTree::drawIt()
{
	treeDraw();
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
