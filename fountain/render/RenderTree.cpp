#include "RenderTree.h"
#include <GL/glew.h>

using fei::RenderTree;

RenderTree::RenderTree()
: root(nullptr)
{
}

void RenderTree::update()
{
	if (root) {
		root->update();
	}
	childList.update();
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
