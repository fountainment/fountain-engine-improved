#include "util/FSM.h"

using fut::FSM;

FSM::FSM()
: _state(NoneState)
{
}

void FSM::inputSignal(int signal)
{
	int result = _fsmMap[_state][signal];
	if (result != NoneSig) {
		setState(result);
	}
}

int FSM::registerSignal(const std::string& signal)
{
	int signalId = getSignalId(signal);
	if (NoneSig == signalId) {
		signalId = registerSignal();
	}
	_nameSignalMap[signal] = signalId;
	_signalNameMap[signalId] = signal;
	return signalId;
}

int FSM::registerState(const std::string& state)
{
	int stateId = getStateId(state);
	if (NoneState == stateId) {
		stateId = registerState();
	}
	_nameStateMap[state] = stateId;
	_stateNameMap[stateId] = state;
	return stateId;
}

void FSM::registerLink(const std::string& curState, \
		const std::string& nextState, const std::string& signal)
{
	int curStateId = registerState(curState);
	int nextStateId = registerState(nextState);
	int signalId = registerSignal(signal);

	registerLink(curStateId, nextStateId, signalId);
}

int FSM::registerSignal()
{
	return ++_maxSignal;
}

int FSM::registerState()
{
	return ++_maxState;
}

void FSM::registerLink(int curState, int nextState, int signal)
{
	_fsmMap[curState][signal] = nextState;
}

int FSM::getSignalId(const std::string& signal)
{
	auto it = _nameSignalMap.find(signal);
	if (it != _nameSignalMap.end()) {
		return it->second;
	}
	return NoneSig;
}

int FSM::getStateId(const std::string& state)
{
	auto it = _nameStateMap.find(state);
	if (it != _nameStateMap.end()) {
		return it->second;
	}
	return NoneState;
}

const std::string FSM::getSignalName(int signal)
{
	auto it = _signalNameMap.find(signal);
	if (it != _signalNameMap.end()) {
		return it->second;
	}
	return fei::EmptyStr;
}

const std::string FSM::getStateName(int state)
{
	auto it = _stateNameMap.find(state);
	if (it != _stateNameMap.end()) {
		return it->second;
	}
	return fei::EmptyStr;
}

const std::vector<std::pair<int, std::string>> FSM::getSignalVector()
{
	return std::vector<std::pair<int, std::string>>(_signalNameMap.begin(), _signalNameMap.end());
}

const std::vector<std::pair<int, std::string>> FSM::getStateVector()
{
	return std::vector<std::pair<int, std::string>>(_stateNameMap.begin(), _stateNameMap.end());
}

const std::vector<std::pair<int, int>> FSM::getStateLinkVector(int state)
{
	std::vector<std::pair<int, int>> ret;
	auto it = _fsmMap.find(state);
	if (it != _fsmMap.end()) {
		ret = std::vector<std::pair<int, int>>(it->second.begin(), it->second.end());
	}
	return ret;
}

const std::vector<std::pair<int, int>> FSM::getStateLinkVector(const std::string& state)
{
	return getStateLinkVector(getStateId(state));
}

const std::vector<int> FSM::getLinkSignalVector(int stateA, int stateB)
{
	std::vector<int> ret;
	auto slv = getStateLinkVector(stateA);
	for (auto sl : slv) {
		if (sl.second == stateB) {
			ret.push_back(sl.first);
		}
	}
	return ret;
}

int FSM::getState()
{
	return _state;
}

void FSM::setState(int state)
{
	if (_state != state) {
		_state = state;
		outputSignal(ChangeSig);
	}
}

void FSM::outputSignal(int signal)
{
}
