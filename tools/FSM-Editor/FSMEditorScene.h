#if !defined(_FSMEDITORSCENE_H_)
#define _FSMEDITORSCENE_H_

#include <fountain.h>
#include <util/FSM.h>

class ButtonBase : public fei::Button
{
public:
	ButtonBase();

	void init() override;

	void onEnter() override;
	void onLeave() override;
	void onMouseDown() override;
	void onMouseUp() override;
};

class SignalButton : public ButtonBase
{
public:
	SignalButton(int sig);

	void onClick() override;
	void update() override;

private:
	int _sig;
};

class StateButton : public ButtonBase
{
public:
	StateButton();

	void onClick() override;
	void update() override;
};

class FSMEditorScene : public fei::Scene
{
public:
	void init() override;
	void update() override;

	void updateSignalList();
	void updateFSM();

private:
	fei::Camera _mainCam;

	fut::FSM _fsm;
	fei::Layer _helpLayer;
	fei::Layer _signalListLayer;
	fei::Layer _fsmLayer;

	fei::Rect _rect;
	fei::ShapeObj _rectObj;
};

#endif // _FEIEDITORSCENE_H_
