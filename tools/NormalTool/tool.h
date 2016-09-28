#ifndef _TOOL_H_
#define _TOOL_H_

#include "fountain.h"

class NormalTool : public fei::Application
{
public:
        void engineSetting(fei::Engine* engine);
	static fei::FountainShader* getShader();
	static fei::FontCache* getFont();

	static fei::FountainShader shader_;
	static fei::FontCache font_;
};

class ColorButton : public fei::Button
{
public:
	virtual void init() override
	{
		getLabel()->setCenterAligned(true);
		getLabel()->setPosition(getRectSize() * 0.5f);
		getLabel()->move(fei::Vec2(0.0f, -10.0f));
	}

	virtual void onEnter() override
	{
		setFrontColor(fei::Color::White);
	}

	virtual void onLeave() override
	{
		setFrontColor(fei::Color::Black);
	}

	virtual void onClick() override
	{
		auto window = fei::Interface::getInstance()->getCurrentWindow();
		window->setClipboard(getName());
	}
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

	fei::Label _eulerLabel;
	fei::Label _normalLabel;
	ColorButton _colorButton;
	fei::Layer _uiLayer;
};

#endif // _TOOL_H_

