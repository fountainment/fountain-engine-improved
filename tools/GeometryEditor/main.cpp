#include "fountain.h"
#include "EditorScene.h"

using namespace fei;

class GeometryEditor : public Application
{
public:
	void engineSetting(Engine* engine)
	{
		engine->window->setResizable(true);
		engine->window->setSize(800.0f, 600.0f);
		engine->window->setTitle("GeometryEditor v0.07");
		engine->window->sceneManager->gotoScene(new EditorScene);
	}
};

int main()
{
	GeometryEditor app;
	app.run();
	return 0;
}
