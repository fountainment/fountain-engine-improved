#ifndef _FEI_SPRITE_H_
#define _FEI_SPRITE_H_

#include "base/basedef.h"
#include "render/RenderList.h"
#include "sprite/Component.h"

namespace fei {

class Sprite : public RenderList
{
public:
	void addComponent(Component* component);
	void delComponent(Component* component);
	void clearComponent();

	void componentBasicUpdate();
	void componentBeforeDraw();
	void componentAfterDraw();
	void componentUpdate();

	virtual void feiBasicUpdate() override;
	virtual void beforeDraw() override;
	virtual void afterDraw() override;
	virtual void update() override;

private:
	std::vector<Component*> _componentList;
};

} // namespace fei

#endif // _FEI_SPRITE_H_
