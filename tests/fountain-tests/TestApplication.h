#if !defined(_TESTAPPLICATION_H_)
#define _TESTAPPLICATION_H_

class TestApplication : public fei::Application
{
public:
	void engineSetting(fei::Engine *eg) override;
};

void test();

#endif
