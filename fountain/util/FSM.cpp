#include "util/FSM.h"

using fut::FSM;

FSM::FSM()
: _state(NONE_SIG)
{
}

void FSM::inputSignal(int signal)
{
	int result = _fsmMap[_state][signal];
	if (result != NONE_SIG) {
		setState(result);
	}
}

int FSM::registerSignal(const std::string& signal)
{
	auto it = _nameSignalMap.find(signal);
	if (it != _nameSignalMap.end()) {
		return it->second;
	}
	int signalIndex = registerSignal();
	_nameSignalMap[signal] = signalIndex;
	_signalNameMap[signalIndex] = signal;
	return signalIndex;
}

int FSM::registerState(const std::string& state)
{
	auto it = _nameStateMap.find(state);
	if (it != _nameStateMap.end()) {
		return it->second;
	}
	int stateIndex = registerState();
	_nameStateMap[state] = stateIndex;
	_stateNameMap[stateIndex] = state;
	return stateIndex;
}

void FSM::registerLink(const std::string& curState, \
		const std::string& nextState, const std::string& signal)
{
	int curStateIndex = registerState(curState);
	int nextStateIndex = registerState(nextState);
	int signalIndex = registerSignal(signal);

	registerLink(curStateIndex, nextStateIndex, signalIndex);
}

int FSM::registerSignal()
{
	return ++_MAX_SIG;
}

int FSM::registerState()
{
	return ++_MAX_STATE;
}

void FSM::registerLink(int curState, int nextState, int signal)
{
	_fsmMap[curState][signal] = nextState;
}

int FSM::getState()
{
	return _state;
}

void FSM::setState(int state)
{
	if (_state != state) {
		_state = state;
		outputSignal(CHANGE_SIG);
	}
}

void FSM::outputSignal(int signal)
{
}
