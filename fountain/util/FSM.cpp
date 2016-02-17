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

void FSM::inputSignal(const std::string& signal)
{
	inputSignal(getSignalId(signal));
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

const std::vector<int> FSM::registerSignal(const std::vector<std::string> signalList)
{
	std::vector<int> ret;
	for (const auto& signal : signalList) {
		ret.push_back(registerSignal(signal));
	}
	return ret;
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

const std::vector<int> FSM::registerState(const std::vector<std::string> stateList)
{
	std::vector<int> ret;
	for (const auto& state : stateList) {
		ret.push_back(registerState(state));
	}
	return ret;
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

void FSM::clearAll()
{
	_state = NoneState;
	_maxSignal = 1;
	_maxState = 1;
	_nameSignalMap.clear();
	_signalNameMap.clear();
	_nameStateMap.clear();
	_stateNameMap.clear();
	_fsmMap.clear();
}

int FSM::getState()
{
	return _state;
}

const std::string FSM::getStateName()
{
	return getStateName(getState());
}

void FSM::setState(int state)
{
	if (_state != state) {
		_state = state;
		outputSignal(ChangeSig);
	}
}

void FSM::setState(const std::string& state)
{
	setState(getStateId(state));
}

void FSM::dump(const std::string& filename)
{
	auto file = std::fopen(filename.c_str(), "wb");
	std::fprintf(file, "%s\n", "#FSM");
	for (const auto& stateMap : _fsmMap) {
		std::string stateA = getStateName(stateMap.first);
		for (const auto& singleLink : stateMap.second) {
			std::string stateB = getStateName(singleLink.second);
			std::string signal = getSignalName(singleLink.first);
			std::fprintf(file, "%s %s %s\n", stateA.c_str(), stateB.c_str(), signal.c_str());
		}
	}
	std::fclose(file);
}

void FSM::load(const std::string& filename)
{
	char a[50], b[50], s[50];
	auto file = std::fopen(filename.c_str(), "rb");
	if (!file) {
		return;
	}
	clearAll();
	std::fscanf(file, "%s", a);
	while (std::fscanf(file, "%s%s%s", a, b, s) != EOF) {
		registerLink(a, b, s);
	}
	std::fclose(file);
}

void FSM::outputSignal(int signal)
{
}
