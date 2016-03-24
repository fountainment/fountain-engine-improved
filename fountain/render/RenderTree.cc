#include "render/RenderTree.h"

#include <GL/glew.h>

using fei::RenderTree;

RenderTree::RenderTree()
: _root(nullptr)
{
}

void RenderTree::treeInit()
{
	if (_root) {
		_root->feiInit();
	}
	_childList.feiInit();
}

void RenderTree::treeDestroy()
{
	_childList.feiDestroy();
	if (_root) {
		_root->feiDestroy();
	}
}

void RenderTree::treeUpdate()
{
	if (_root) {
		_root->feiUpdate();
	}
	_childList.feiUpdate();
}

void RenderTree::treeDraw()
{
	glPushMatrix();
	if (_root) {
		_root->draw();
	}
	_childList.draw();
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

void RenderTree::feiBasicUpdate()
{
	treeUpdate();
}

void RenderTree::drawIt()
{
	treeDraw();
}

void RenderTree::setRoot(RenderObj* rObj)
{
	_root = rObj;
}

void RenderTree::addChild(RenderObj* rObj)
{
	if (_isLoaded) {
		rObj->feiInit();
	}
	_childList.add(rObj);
}

void RenderTree::delChild(RenderObj* rObj)
{
	_childList.del(rObj);
}

void RenderTree::sort()
{
	_childList.sort();
}
