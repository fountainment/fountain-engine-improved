#if !defined(_EDITORSCENE_H_)
#define _EDITORSCENE_H_

#include "fountain.h"
#include "util/PhysicsAnime.h"

class EShapeObj : public fei::ShapeObj
{
public:
	void drawIt() override;
};

class Cross : public fei::RenderObj
{
public:
	void drawIt() override;
	void setSize(float sz);

private:
	fei::Segment a, b;
};

class EditorScene : public fei::Scene
{
public:
	void init() override;
	void update() override;

	void loadAnime(const std::string& path);

	void loadAnchorOffset();
	void loadGroup();
	void saveIpi();
	void saveAnchorOffset();

	void mouseButtonCallback(int button, int action, int mods) override;
	void cursorPosCallback(double xpos, double ypos) override;
	void scrollCallback(double xoffset, double yoffset) override;
	void keyCallback(int key, int scancode, int action, int mods) override;
	void framebufferSizeCallback(int width, int height) override;
	void dropCallback(int count, const char** paths) override;

private:
	fei::Camera mainCam;
	fei::Polygon poly[10];
	fei::Texture tex[10];

	fei::Body* animeBody;
	fei::RenderObj animeObj;
	fut::CollisionFrameAnime anime[10];
	std::string ipiName;
	std::string _ipiFileName;

	fei::Image image;
	EShapeObj polyObj;

	Cross centerCross;

	int curEdit;

	int holdVertex;
	fei::Vec2 _pos, _vertexPos;
	fei::Vec2 mPos, oldPos, deltaV;

	std::map<std::string, fei::Vec2> _ipiNameToAnchorOffset;
	std::map<int, std::vector<std::string>> _groupIndexToIpiNameList;
	std::map<std::string, int> _ipiNameToGroupIndex;
};

#endif
