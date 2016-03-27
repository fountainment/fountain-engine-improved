#include "fountain.h"

#include "editor.h"

using namespace fei;

class TestApplication : public Application
{
public:
	void engineSetting(Engine* engine)
	{
		engine->getWindow()->setTitle("CollisionEditor");
		engine->getWindow()->setSize(800, 600);
		engine->getWindow()->getSceneManager()->gotoScene(new EditorScene);
	}
};

int main()
{
	TestApplication testApp;
	testApp.run();
	return 0;
}
