#if !defined(_EDITORSCENE_H_)
#define _EDITORSCENE_H_

#include "fountain.h"

class EShapeObj : public fei::ShapeObj
{
public:
	void drawIt() override
	{
		fei::Render::getInstance()->drawShape(shape);
		fei::Rect rct;
		rct.setSize(fei::Vec2(10.0f));
		const float *data = shape->getDataPtr();
		for (int i = 0; i < shape->getDataSize(); i++) {
			rct.setCenter(fei::Vec2(data[i << 1], data[i << 1 | 1]));
			fei::Render::getInstance()->drawShape(&rct);
		}
	}
};

class EditorScene : public fei::Scene
{
public:
	void init() override;
	void update() override;

	void mouseButtonCallback(int button, int action, int mods) override;
	void cursorPosCallback(double xpos, double ypos) override;
	void scrollCallback(double xoffset, double yoffset) override;
	void keyCallback(int key, int scancode, int action, int mods) override;

private:
	fei::Camera mainCam;
	fei::Polygon poly;
	EShapeObj polyObj;

	int holdVertex;
	fei::Vec2 pos;
};

#endif
