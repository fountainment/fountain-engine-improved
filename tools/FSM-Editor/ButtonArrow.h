#if !defined(_BUTTONARROW_H_)
#define _BUTTONARROW_H_

#include "math/Segment.h"
#include "render/RenderObj.h"
#include "ui/Button.h"

class ButtonArrow : public fei::RenderObj
{
public:
	ButtonArrow(fei::Button* ba, fei::Button* bb);

	virtual void drawIt() override;

private:
	fei::Button* _ba;
	fei::Button* _bb;
	fei::Segment seg;
};

#endif // _BUTTONARROW_H_
