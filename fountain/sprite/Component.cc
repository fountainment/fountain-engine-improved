#include "Component.h"

#include "sprite/Sprite.h"

using fei::Component;

Component::Component()
: _sprite(nullptr)
{
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

void Component::setSprite(fei::Sprite* sprite)
{
	_sprite = sprite;
}
