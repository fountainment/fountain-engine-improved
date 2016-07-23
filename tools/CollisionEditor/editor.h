#ifndef _TOOLS_COLLISIONEDITOR_H_
#define _TOOLS_COLLISIONEDITOR_H_

#include "fountain.h"
#include "util/PhysicsAnime.h"
#include "util/VimStyleCommandLabel.h"

class EditorScene : public fei::Scene
{
public:
	enum class EditState {
		NONE = 0,
		RECT = 1,
		CIRCLE = 2,
		POLYGON = 3,
		SEGMENT = 4
	};

	virtual void init() override;
	virtual void update() override;

	void initUILayout();

	void clearEditState();
	void editRect();
	void editCircle();
	void editPolygon();
	void editSegment();
	void editNone();

	void loadFile(const char* filename);
	void loadImage(const char* filename);
	void loadSIP(const char* filename);
	void loadIPI(const char* filename);
	void loadPos(const char* filename);
	void save();

	void unloadImage();

	const fei::Vec2 getCursorWorldPos();

	virtual void keyCallback(int key, int scancode, int action, int mods) override;
	virtual void charactorCallback(unsigned int codepoint) override;
	virtual void scrollCallback(double xoffset, double yoffset) override;
	virtual void mouseButtonCallback(int button, int action, int mods) override;
	virtual void dropCallback(int count, const char** paths) override;

private:
	fei::Camera _camera;
	fei::Camera _uiCamera;
	fei::Layer _imagePoolLayer;
	fei::Layer _uiLayer;
	fei::FontCache _fontCache;
	fut::VimStyleCommandLabel _commandLabel;
	fei::Texture _texture;
	EditState _editState;
	fei::ShapeObj _editShapeObj;
	fei::Rect _editRect;
	fei::Circle _editCircle;
	fei::Polygon _editPolygon;
	fei::Segment _editSegment;
	bool _mouseDown;
	bool _needInitUILayout;
	fei::Vec2 _mouseDownPos;
	std::list<fei::Rect> _rectList;
	std::list<fei::Circle> _circleList;
	std::list<fei::Polygon> _polygonList;
	std::list<fei::Segment> _segmentList;
	std::list<fei::Shape*> _shapeList;
	std::map<fei::Shape*, fei::Body*> _shapeBodyMap;
	std::string _saveName;

	fei::RenderObj _animeObj;
	fut::CollisionFrameAnime _anime;
};

#endif // _TOOLS_COLLISIONEDITOR_H_
