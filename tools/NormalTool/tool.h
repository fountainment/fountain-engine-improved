#ifndef _TOOL_H_
#define _TOOL_H_

#include "fountain.h"

class NormalTool : public fei::Application
{
public:
        void engineSetting(fei::Engine* engine);
	static fei::FountainShader* getShader();

	static fei::FountainShader shader_;
};

class ToolScene : public fei::Scene
{
public:
	virtual void init() override;
	virtual void update() override;

	void resetPlane();
	void rotatePlane(const fei::Vec2& v);

	virtual void keyCallback(int key, int scancode, int action, int mods);

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

