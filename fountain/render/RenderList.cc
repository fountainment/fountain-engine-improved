#include "render/RenderList.h"

#include "render/Render.h"

using fei::RenderList;

#define MAX_RENDERLIST_SIZE 1000

std::vector<std::vector<int>> RenderList::dag_(MAX_RENDERLIST_SIZE);
std::vector<int> RenderList::ind_(MAX_RENDERLIST_SIZE);

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
	fei::RenderObj::feiBasicUpdate();
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
	return _objList;
}

void RenderList::listRearrange(std::vector<int> newIndex)
{
	auto cp = getListVector();
	int sz = static_cast<int>(cp.size());
	for (int i = 0; i < sz; i++) {
		_objList[i] = cp[newIndex[i]];
	}
}

void RenderList::garbageRecycle()
{
	while (!_garbageQueue.empty()) {
		auto garbage = _garbageQueue.front();
		_garbageQueue.pop();
		delete garbage;
	}
}

void RenderList::sort(std::function<bool(fei::RenderObj*, fei::RenderObj*)> cmp)
{
	std::sort(_objList.begin(), _objList.end(), cmp);
}

void RenderList::topoSort(std::function<int(fei::RenderObj*, fei::RenderObj*)> cmp)
{
	int num = _objList.size();
	for (int i = 0; i < num; i++) {
		dag_[i].clear();
		ind_[i] = 0;
	}
	for (int i = 0; i < num; i++) {
		for (int j = i + 1; j < num; j++) {
			int t = cmp(_objList[i], _objList[j]);
			if (t == 0) {
				continue;
			}
			if (t > 0) {
				dag_[j].push_back(i);
				ind_[i]++;
			} else {
				dag_[i].push_back(j);
				ind_[j]++;
			}
		}
	}
	std::vector<int> result;
	std::queue<int> q;
	for (int i = 0; i < num; i++) {
		if (ind_[i] == 0) {
			q.push(i);
		}
	}
	while (!q.empty()) {
		int t = q.front();
		result.push_back(t);
		q.pop();
		for (auto i : dag_[t]) {
			ind_[i]--;
			if (ind_[i] == 0) {
				q.push(i);
			}
		}
	}
	for (int i = 0; i < num; i++) {
		if (ind_[i] != 0) {
			result.push_back(i);
		}
	}
	listRearrange(result);
}

bool fei::RenderListZCmp(fei::RenderObj* a, fei::RenderObj* b)
{
	return a->getZPos() < b->getZPos();
}
