#ifndef _FEI_COMPONENT_H_
#define _FEI_COMPONENT_H_

namespace fei {

class Sprite;

class Component
{
public:
	friend class Sprite;

	Component();
	virtual ~Component();

	Sprite* getSprite();

	virtual void basicUpdate();
	virtual void update();
	virtual void beforeDraw();
	virtual void afterDraw();

	void setPrivate(bool isPrivate);

private:
	void setSprite(Sprite* sprite);

	Sprite* _sprite;
	bool _isPrivate;
};

} // namespace fei

#endif // _FEI_COMPONENT_H_
