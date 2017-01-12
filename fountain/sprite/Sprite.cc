#include "sprite/Sprite.h"

using fei::Sprite;

Sprite::~Sprite()
{
	clearComponent();
}

void Sprite::addComponent(fei::Component* component)
{
	auto sprite = component->getSprite();
	if (sprite) {
		sprite->delComponent(component);
	}
	component->setSprite(this);
	_componentList.push_back(component);
}

void Sprite::delComponent(fei::Component* component)
{
	component->setSprite(nullptr);
	auto it = std::find(_componentList.begin(), _componentList.end(), component);
		if (it != _componentList.end()) {
		_componentList.erase(it);
	}
}

void Sprite::clearComponent()
{
	for (auto component : _componentList) {
		auto sprite = component->getSprite();
		if (sprite == this) {
			component->setSprite(nullptr);
		}
	}
}

void Sprite::componentBasicUpdate()
{
	for (auto component : _componentList) {
		component->basicUpdate(this);
	}
}

void Sprite::componentBeforeDraw()
{
	for (auto component : _componentList) {
		component->beforeDraw(this);
	}
}

void Sprite::componentAfterDraw()
{
	for (auto component : _componentList) {
		component->afterDraw(this);
	}
}

void Sprite::componentUpdate()
{
	for (auto component : _componentList) {
		component->update(this);
	}
}

void Sprite::feiBasicUpdate()
{
	fei::RenderList::feiBasicUpdate();
	componentBasicUpdate();
}

void Sprite::beforeDraw()
{
	fei::RenderList::beforeDraw();
	componentBeforeDraw();
}

void Sprite::afterDraw()
{
	fei::RenderList::afterDraw();
	componentAfterDraw();
}

void Sprite::update()
{
	fei::RenderList::update();
	componentUpdate();
}
