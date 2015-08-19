#if !defined(_FEI_CONTROL_H_)
#define _FEI_CONTROL_H_

#include "base/ModuleBase.h"
#include "control/Joystick.h"

namespace fei {

class Control : public fei::ModuleBase
{
public:
	bool init() override;
	void destroy() override;

	void executeBeforeFrame() override;

	int findJoystick();
	bool joystickCheck();
	Joystick* getJoystick();

	static Control* getInstance();
private:
	Control();

	Joystick joystick;

	static Control *instance;
};

}

#endif
