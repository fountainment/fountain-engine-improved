#if !defined(_EDITORSCENE_H_)
#define _EDITORSCENE_H_

#include "fountain.h"

class EditorScene : public fei::Scene
{
public:
	void init() override;
	void update() override;

	void mouseButtonCallback(int button, int action, int mods) override;
	void cursorPosCallback(double xpos, double ypos) override;
	void scrollCallback(double xoffset, double yoffset) override;

private:
	fei::Camera mainCam;
	fei::Polygon poly;
	fei::ShapeObj polyObj;

	int holdVertex;
	fei::Vec2 pos;
};

#endif
