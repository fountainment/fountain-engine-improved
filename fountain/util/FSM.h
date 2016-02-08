#if !defined(_FUT_FSM_H_)
#define _FUT_FSM_H_

#include "base/basedef.h"

namespace fut {

class FSM
{
public:
	FSM();

	void inputSignal(int signal);

	int registerSignal(const std::string& signal);
	int registerState(const std::string& state);
	void registerLink(const std::string& curState, \
			const std::string& nextState, const std::string& signal);

	int registerSignal();
	int registerState();
	void registerLink(int curState, int nextState, int signal);

	int getSignalId(const std::string& signal);
	int getStateId(const std::string& state);
	const std::string getSignalName(int signal);
	const std::string getStateName(int state);

	const std::vector<std::pair<int, std::string>> getSignalVector();
	const std::vector<std::pair<int, std::string>> getStateVector();
	//const std::vector<std::pair<int, int>> getLinkVector();
	const std::vector<std::pair<int, int>> getStateLinkVector(int state);
	const std::vector<std::pair<int, int>> getStateLinkVector(const std::string& state);

	int getState();
	void setState(int state);

	static const int NoneSig = 0;
	static const int ChangeSig = 1;
	static const int NoneState = 0;

private:
	virtual void outputSignal(int signal);

	int _maxSignal = 1;
	int _maxState = 1;
	int _state;
	std::map<std::string, int> _nameSignalMap;
	std::map<int, std::string> _signalNameMap;
	std::map<std::string, int> _nameStateMap;
	std::map<int, std::string> _stateNameMap;
	std::map<int, std::map<int, int>> _fsmMap;
};

} // namespace fut

#endif // _FUT_FSM_H_
