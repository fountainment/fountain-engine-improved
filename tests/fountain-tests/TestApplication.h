#if !defined(_TESTAPPLICATION_H_)
#define _TESTAPPLICATION_H_

#include "fountain.h"

class TestApplication : public fei::Application
{
public:
	static fei::FontCache font;

	void engineSetting(fei::Engine *eg) override;
};

#endif
