#if !defined(_FEI_BUTTON_H_)
#define _FEI_BUTTON_H_

//TODO: finish class Button

#include "font/FontCache.h"
#include "render/Camera.h"
#include "render/Image.h"
#include "render/RenderObj.h"
#include "math/Rect.h"
#include "ui/Label.h"

namespace fei {

class Button : public RenderObj
{
public:
	Button();

	void drawIt() override;
	void feiUpdate() override;

	void setLabel(const Label& label);
	fei::Label* getLabel();

	void setRectSize(const Vec2& rectSize);
	const Vec2 getRectSize();

	void setBackColor(const Color& color);
	void setFrontColor(const Color& color);

	void setBackImage(const Image& image);

	void setLabelString(FontCache& fontCache, const std::string& str);
	void setLabelCenterAligned(bool b);

	const Vec2 getCenter();
	void setCenter(const Vec2& v);

	bool isCollide();
	bool isButtonDown();

	void click();

private:
	virtual void onEnter();
	virtual void onLeave();
	virtual void onCollide();
	virtual void onMouseDown();
	virtual void onButtonDown();
	virtual void onClick();
	virtual void onButtonUp();
	virtual void onMouseUp();

	Camera* _drawCamera;
	Rect _backRect;
	Image _backImage;
	Label _label;

	Color _backColor;
	Color _frontColor;

	bool _collide;
	bool _mouseDown;
	bool _buttonDown;
};

} // namespace fei

#endif // _FEI_BUTTON_H_
