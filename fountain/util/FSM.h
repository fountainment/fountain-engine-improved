#if !defined(_FUT_FSM_H_)
#define _FUT_FSM_H_

#include <string>
#include <map>
#include <vector>

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

	const std::vector<std::pair<int, std::string>> getSignalVector();
	const std::vector<std::pair<int, std::string>> getStateVector();

	int getState();
	void setState(int state);

	static const int NONE_SIG = 0;
	static const int CHANGE_SIG = 1;

private:
	virtual void outputSignal(int signal);

	int _MAX_SIG = 1;
	int _MAX_STATE = 1;
	int _state;
	std::map<std::string, int> _nameSignalMap;
	std::map<int, std::string> _signalNameMap;
	std::map<std::string, int> _nameStateMap;
	std::map<int, std::string> _stateNameMap;
	std::map<int, std::map<int, int>> _fsmMap;
};

} // namespace fut

#endif // _FUT_FSM_H_
