#if !defined(_FEI_BUTTON_H_)
#define _FEI_BUTTON_H_

//TODO: finish class Button

#include "render/RenderObj.h"
#include "render/Camera.h"
#include "render/Image.h"
#include "font/FontCache.h"
#include "ui/Label.h"
#include "math/Rect.h"

namespace fei {

class Button : public RenderObj
{
public:
	Button();

	void drawIt() override;
	void feiUpdate() override;

	void setLabel(const Label& label);

	void setRectSize(const Vec2& rectSize);

	void setBackColor(const Color& color);
	void setFrontColor(const Color& color);

	void setLabelString(FontCache& fontCache, const std::string& str);

private:
	virtual void onEnter();
	virtual void onLeave();
	virtual void onCollide();
	virtual void onClick();

	Camera* _drawCamera;
	Rect _backRect;
	Image _backImage;
	Label _label;

	Color _backColor;
	Color _frontColor;

	bool _collide;
};

}

#endif
