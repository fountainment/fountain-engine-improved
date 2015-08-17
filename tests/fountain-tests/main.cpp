#include "fountain.h"

fei::Texture tex;

void test()
{
	tex.draw();
	char *buffer = fei::readFileBuffer("1.txt");
	if (buffer) {
		std::printf("%s", buffer);
		delete [] buffer;
	}
	std::printf("Time: %f    Frame: %lld\n", fei::Time::getInstance()->getTime(), fei::Time::getInstance()->getFrame());
}

class TestApplication : public fei::Application
{
public:
	void engineSetting(fei::Engine *eg) override
	{
		if (!eg) return;
		eg->window->setSize(800, 600);
		eg->window->setTitle("fountain-tests");
		eg->window->setResizable(false);

		eg->setFrameFunc(test);

		fei::Render::getInstance()->setViewport(fei::Rect(0, 0, 800, 600));

		tex.loadFile("test.png");

		//fei::Math::getInstance()->setRandomSeed(9312);
		//fei::Render::getInstance()->setClearColor(FEI_Blue);

		//fei::Scene::getInstance()->gotoScene(new TestScene());
	}
};

int main()
{
	TestApplication testApp;
	testApp.run();
	return 0;
}
