#ifndef _FEI_COMPONENT_H_
#define _FEI_COMPONENT_H_

namespace fei {

class Sprite;

class Component
{
public:
	friend class Sprite;

	Component();

	Sprite* getSprite();

	virtual void basicUpdate();
	virtual void update();
	virtual void beforeDraw();
	virtual void afterDraw();

private:
	void setSprite(Sprite* sprite);

	Sprite* _sprite;
};

} // namespace fei

#endif // _FEI_COMPONENT_H_
