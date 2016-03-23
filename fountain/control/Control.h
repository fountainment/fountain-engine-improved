#ifndef _FEI_CONTROL_H_
#define _FEI_CONTROL_H_

#include "base/ModuleBase.h"
#include "control/Joystick.h"

namespace fei {

class Control : public fei::ModuleBase
{
public:
	bool init() override;

	void executeBeforeFrame() override;

	int findJoystick();
	bool joystickCheck();
	Joystick* getJoystick();

	static Control* getInstance();

private:
	Control();

	Joystick _joystick;

	static Control *instance_;
};

} // namespace fei

#endif // _FEI_CONTROL_H_
