#if !defined(_TESTSCENE_H_)
#define _TESTSCENE_H_

#include "fountain.h"
#include "Charactor.h"

class TestScene : public fei::Scene
{
public:
	void init() override;
	void destroy() override;
	void update() override;

private:
	fei::Clock mainClock;
	fei::Camera mainCam, UICam;
	fei::Texture UI, map;
	fei::Layer UILayer;
	fei::Source audio;
	Charactor mainChar;

	fei::Texture bomber;
	fei::Texture bomberNormal;
	fei::ShaderProgram normalShader;

	fei::Body *ground[4];

	float pitch;
};

#endif
