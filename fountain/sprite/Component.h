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

	virtual void basicUpdate(Sprite* sprite);
	virtual void update(Sprite* sprite);
	virtual void beforeDraw(Sprite* sprite);
	virtual void afterDraw(Sprite* sprite);

	void setPrivate(bool isPrivate);

private:
	void setSprite(Sprite* sprite);

	Sprite* _sprite;
	bool _isPrivate;
};

} // namespace fei

#endif // _FEI_COMPONENT_H_
