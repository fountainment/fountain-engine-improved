#include "fountain.h"
#include "EditorScene.h"

using namespace fei;

class GeometryEditor : public Application
{
public:
	void engineSetting(Engine* engine)
	{
		engine->window->setFullscreen(true);
		engine->window->sceneManager->gotoScene(new EditorScene);
	}
};

int main()
{
	GeometryEditor app;
	app.run();
	return 0;
}
