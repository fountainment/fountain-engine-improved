#ifndef _TOOLS_COLLISIONEDITOR_H_
#define _TOOLS_COLLISIONEDITOR_H_

#include "fountain.h"
#include "util/VimStyleCommandLabel.h"

class EditorScene : public fei::Scene
{
public:
	enum class EditState {
		NONE = 0,
		RECT = 1,
		CIRCLE = 2
	};

	virtual void init() override;
	virtual void update() override;

	void initUILayout();

	void clearEditState();
	void editRect();
	void editCircle();

	const fei::Vec2 getCursorWorldPos();

	virtual void keyCallback(int key, int scancode, int action, int mods) override;
	virtual void charactorCallback(unsigned int codepoint) override;
	virtual void scrollCallback(double xoffset, double yoffset) override;
	virtual void mouseButtonCallback(int button, int action, int mods) override;


private:
	fei::Camera _camera;
	fei::Camera _uiCamera;
	fei::Layer _uiLayer;
	fei::FontCache _fontCache;
	fut::VimStyleCommandLabel _commandLabel;
	fei::Texture _texture;
	EditState _editState;
	fei::ShapeObj _editShapeObj;
	fei::Rect _editRect;
	fei::Circle _editCircle;
	fei::Polygon _editPolygon;
	bool _mouseDown;
	bool _needInitUILayout;
	fei::Vec2 _mouseDownPos;
	std::list<fei::Rect> _rectList;
	std::list<fei::Circle> _circleList;
	std::list<fei::Shape*> _shapeList;
	std::map<fei::Shape*, fei::Body*> _shapeBodyMap;
};

#endif // _TOOLS_COLLISIONEDITOR_H_
