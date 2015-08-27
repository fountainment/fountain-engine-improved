#if !defined(_TESTAPPLICATION_H_)
#define _TESTAPPLICATION_H_

#include "fountain.h"

using namespace fei;

class TestApplication : public Application
{
public:
	void engineSetting(Engine *eg) override;
};

#endif
