#if !defined(_FSMEDITORSCENE_H_)
#define _FSMEDITORSCENE_H_

#include <fountain.h>
#include <util/FSM.h>

class SignalButton : public fei::Button
{
public:
	SignalButton(int sig);
	void init() override;

	void onEnter() override;
	void onLeave() override;
	void update() override;

private:
	int _sig;
};

class FSMEditorScene : public fei::Scene
{
public:
	void init() override;
	void update() override;

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
