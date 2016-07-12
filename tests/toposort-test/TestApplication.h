#ifndef _TESTAPPLICATION_H_
#define _TESTAPPLICATION_H_

#include "fountain.h"

class TopoTest : public fei::Application
{
public:
	void engineSetting(fei::Engine* eg) override;
};

#endif // _TESTAPPLICATION_H_
