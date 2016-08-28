#include "Component.h"

#include "sprite/Sprite.h"

using fei::Component;

Component::Component()
: _sprite(nullptr),
  _isPrivate(false)
{
}

Component::~Component()
{
	if (getSprite()) {
		getSprite()->delComponent(this);
	}
}

fei::Sprite* Component::getSprite()
{
	return _sprite;
}

void Component::basicUpdate()
{
}

void Component::update()
{
}

void Component::beforeDraw()
{
}

void Component::afterDraw()
{
}

void Component::setPrivate(bool isPrivate)
{
	_isPrivate = isPrivate;
}

void Component::setSprite(fei::Sprite* sprite)
{
	if (_isPrivate) {
		_sprite = sprite;
	}
}
