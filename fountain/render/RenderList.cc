#include "render/RenderList.h"

#include "render/Render.h"

using fei::RenderList;

RenderList::~RenderList()
{
	garbageRecycle();
}

void RenderList::listInit()
{
	for (auto renderObj : _objList) {
		renderObj->feiInit();
	}
}

void RenderList::listDestroy()
{
	for (auto it = _objList.rbegin(); it != _objList.rend(); ++it) {
		(*it)->feiDestroy();
	}
}

void RenderList::listUpdate()
{
	auto tmpList = _objList;
	for (auto renderObj : tmpList) {
		renderObj->feiUpdate();
	}
}

void RenderList::listDraw()
{
	for (auto it = _objList.rbegin(); it != _objList.rend(); ++it) {
		if (!(*it)->hasAlpha()) {
			fei::Render::IndependentDraw(*it);
		}
	}
	for (auto renderObj : _objList) {
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

void RenderList::feiBasicUpdate()
{
	listUpdate();
}

void RenderList::drawIt()
{
	listDraw();
}

void RenderList::add(fei::RenderObj* rObj)
{
	auto parent = rObj->getParent();
	if (parent) {
		static_cast<RenderList*>(parent)->del(rObj);
	}
	rObj->setParent(this);
	if (_isLoaded) {
		rObj->feiInit();
	}
	_objList.push_back(rObj);
}

void RenderList::del(fei::RenderObj* rObj)
{
	rObj->setParent(nullptr);
	_objList.erase(std::find(_objList.begin(), _objList.end(), rObj));
}

void RenderList::clear()
{
	for (auto renderObj : _objList) {
		renderObj->setParent(nullptr);
	}
	_objList.clear();
}

void RenderList::throwAway(fei::RenderObj* garbage)
{
	_garbageQueue.push(garbage);
}

void RenderList::throwAwayAll()
{
	for (auto renderObj : _objList) {
		throwAway(renderObj);
	}
}

const std::vector<fei::RenderObj*> RenderList::getListVector()
{
	return std::vector<fei::RenderObj*>(_objList.begin(), _objList.end());
}

void RenderList::garbageRecycle()
{
	while (!_garbageQueue.empty()) {
		auto garbage = _garbageQueue.front();
		_garbageQueue.pop();
		delete garbage;
	}
}

void RenderList::sort(bool (*cmp)(fei::RenderObj*, fei::RenderObj*))
{
	std::sort(_objList.begin(), _objList.end(), cmp);
}

bool fei::RenderListZCmp(fei::RenderObj* a, fei::RenderObj* b)
{
	return a->getZPos() < b->getZPos();
}
