#include "fountain.h"

using namespace fei;

class TestApplication : public Application
{
public:
	void engineSetting(Engine* engine)
	{
	}
};

int main()
{
	TestApplication testApp;
	testApp.run();
	return 0;
}
