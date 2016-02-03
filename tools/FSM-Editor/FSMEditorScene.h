#if !defined(_FSMEDITORSCENE_H_)
#define _FSMEDITORSCENE_H_

#include <fountain.h>
#include <util/FSM.h>

//TODO: add pointer and signalLabel class

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
	StateButton(int state);

	void onClick() override;
	void onButtonDown() override;
	void onButtonUp() override;
	void update() override;

private:
	int _state;
	static StateButton* DownStateButton;
};

class FSMEditorScene : public fei::Scene
{
public:
	void init() override;
	void destroy() override;
	void update() override;

	void updateSignalList();
	void updateFSM();
	void setSignal(int signal);
	void setState(int state);

	void charactorCallback(unsigned int codepoint) override;
	void keyCallback(int key, int scancode, int action, int mods) override;
	void scrollCallback(double xoffset, double yoffset);
	void mouseDrag(fei::Camera* cam, fei::NodeBase* node, float k = 1.0f);

	void refreshWindow();

	std::vector<unsigned long> _tmpName;
	fei::Label _tmpLabel;
	fei::Camera _fsmCam;

	std::map<int, fei::Vec2> _statePositionMap;

private:
	fei::Camera _mainCam;

	fut::FSM _fsm;
	fei::Layer _helpLayer;
	fei::Layer _signalListLayer;
	fei::Layer _fsmLayer;
	fei::Layer _fixLayer;

	fei::Button* _addSignalButton;
	fei::Button* _addStateButton;
	fei::Rect _rect;
	fei::ShapeObj _rectObj;

	fei::Vec2 _cursorDeltaV;
};

#endif // _FEIEDITORSCENE_H_
