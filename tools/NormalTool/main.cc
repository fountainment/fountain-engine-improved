#include "fountain.h"

#include "tool.h"

using namespace fei;

class TestApplication : public Application
{
public:
        void engineSetting(Engine* engine)
	{
		engine->getWindow()->setTitle("NormalTool");
		engine->getWindow()->setSize(1000, 600);
		engine->getWindow()->setSamples(8);
		engine->getWindow()->setVsync(true);
		engine->getWindow()->getSceneManager()->gotoScene(new ToolScene);
	}
};

int main()
{
	TestApplication testApp;
	testApp.run();
	return 0;
}

