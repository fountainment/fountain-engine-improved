#if !defined(_BUTTONARROW_H_)
#define _BUTTONARROW_H_

#include "math/Segment.h"
#include "render/RenderObj.h"
#include "ui/Button.h"
#include "ui/Label.h"

class ButtonArrow : public fei::RenderObj
{
public:
	ButtonArrow(fei::Button* ba, fei::Button* bb, const std::string& labelStr);

	virtual void drawIt() override;

private:
	fei::Button* _ba;
	fei::Button* _bb;
	fei::Segment _seg;
	fei::Label _label;
};

#endif // _BUTTONARROW_H_
