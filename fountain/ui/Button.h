#if !defined(_FEI_BUTTON_H_)
#define _FEI_BUTTON_H_

//TODO: finish class Button

#include "render/RenderObj.h"
#include "render/Camera.h"
#include "render/Image.h"
#include "ui/Label.h"
#include "math/Rect.h"

namespace fei {

class Button : public RenderObj
{
public:
	Button();

	void drawIt() override;
	void update() override;

	virtual void click();

private:
	Camera* _drawCamera;
	Rect _backRect;
	Image _backImage;
	Label _label;
};

}

#endif