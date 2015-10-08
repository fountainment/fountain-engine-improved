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
	if (_isLoaded) return;
	init();
	treeInit();
	_isLoaded = true;
}

void RenderTree::feiDestroy()
{
	if (!_isLoaded) return;
	treeDestroy();
	destroy();
	_isLoaded = false;
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
	if (_isLoaded) {
		rObj->feiInit();
	}
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
