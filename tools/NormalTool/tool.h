#ifndef _TOOL_H_
#define _TOOL_H_

#include "fountain.h"

class ToolScene : public fei::Scene
{
public:
	virtual void init() override;
	virtual void update() override;

private:
	fei::Camera _camera;
	fei::Camera _uiCamera;
	fei::Rect _backRect;
	fei::Rect _rect;
	fei::ShapeObj _backPlane;
	fei::ShapeObj _plane;
	fei::Layer _planeLayer;
	fei::Layer _uiLayer;
};

#endif // _TOOL_H_

