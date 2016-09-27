#include "fountain.h"

#include "tool.h"

using namespace fei;

FountainShader NormalTool::shader_;

void NormalTool::engineSetting(Engine* engine)
{
	auto shader = getShader();
	shader->loadDefault();
	shader->setRenderMode(FountainShader::RENDER_BASIC);
	shader->setUseLight(true);

	auto lightManager = shader->getLightManager();
	lightManager->setLightNum(1);
	auto light = lightManager->getLight(0);
	light->setType(Light::POINT_LIGHT);
	light->setPosition(Vec3(0.0f, 0.0f, 300.0f));
	light->setColor(Vec4(1.0f));
	light->setIntensity(10.0f);
	light->setRadius(300.0f);

	engine->getWindow()->setTitle("NormalTool");
	engine->getWindow()->setSize(1000, 600);
	engine->getWindow()->setSamples(8);
	engine->getWindow()->setVsync(true);
	engine->getWindow()->getSceneManager()->gotoScene(new ToolScene);
}

FountainShader* NormalTool::getShader()
{
	return &shader_;
}

int main()
{
	NormalTool app;
	app.run();
	return 0;
}