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
	virtual ~SignalButton();

	void onClick() override;

private:
	int _sig;
	static SignalButton* selectSignalButton_;
};

class StateButton : public ButtonBase
{
public:
	StateButton(int state);
	virtual ~StateButton();

	void onEnter() override;
	void onLeave() override;

	void onClick() override;
	void onButtonDown() override;
	void onButtonUp() override;
	void beforeUpdate() override;

	int getState();

private:
	int _state;
	static StateButton* downStateButton_;
	static StateButton* selectStateButton_;
};

class FSMEditorScene : public fei::Scene
{
public:
	enum class DisplayType
	{
		SHOW_ALL,
		SHOW_ONE_STATE,
		SHOW_ONE_SIGNAL
	};

	void init() override;
	void destroy() override;
	void beforeUpdate() override;

	void updateStateList();
	void updateSignalList();
	void updateSignalPosition();
	void updateFSM();
	void updateFSMConnection();
	void setSignal(int signal);
	void setState(int state);

	void establishLink(StateButton* a, StateButton* b);
	void deleteLink(StateButton* a, StateButton* b);

	void characterCallback(unsigned int codepoint) override;
	void keyCallback(int key, int scancode, int action, int mods) override;
	void scrollCallback(double xoffset, double yoffset);
	void mouseButtonCallback(int button, int action, int mods);
	void framebufferSizeCallback(int width, int height);
	void mouseDrag(fei::Camera* cam, fei::NodeBase* node, float k = 1.0f);

	bool processCmd(const std::string& cmd);
	void dumpPosition(const std::string& filename);
	void dumpSignal(const std::string& filename);
	void dumpState(const std::string& filename);
	void loadPosition(const std::string& filename);

	void showOnlyOneState();
	void showOnlyOneSignal();
	void showAll();

	void refreshWindow();

	std::vector<unsigned long> _tmpName;
	fei::Label _tmpLabel;
	fei::Camera _fsmCam;

	std::map<int, fei::Vec2> _statePositionMap;
	StateButton* _collideStateButton;
	bool _drawLine;

private:
	fei::Camera _mainCam;

	fut::FSM _fsm;
	fei::Layer _helpLayer;
	fei::Layer _signalListLayer;
	fei::Layer _stateListLayer;
	fei::Layer _lineLayer;
	fei::Layer _editingLineLayer;
	fei::Layer _fixLayer;

	fei::Button* _addSignalButton;
	fei::Button* _addStateButton;
	fei::Rect _rect;
	fei::ShapeObj _rectObj;

	fei::Vec2 _cursorDeltaV;

	int _currentSignal;
	int _currentState;

	bool _needUIRefresh;

	std::string _openFile;

	StateButton* _startStateButton;
	StateButton* _endStateButton;

	fei::Segment _editingLine;
	fei::ShapeObj _editingLineObj;

	DisplayType _displayType;
};

#endif // _FEIEDITORSCENE_H_
