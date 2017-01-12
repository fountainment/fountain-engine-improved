#ifndef _FUT_VIMSTYLECOMMANDLABEL_H_
#define _FUT_VIMSTYLECOMMANDLABEL_H_

#include "base/basedef.h"
#include "ui/Label.h"

#ifdef ERROR
#undef ERROR
#endif

namespace fut {

class CommandResult
{
public:
	enum class Type {
		OK = 0,
		ERROR = 1
	};

	CommandResult() = default;
	CommandResult(CommandResult::Type type, const std::string& result);

	CommandResult::Type _type;
	std::string _result;

	static const CommandResult Ok;
	static const CommandResult Error;
};

class CommandInterpreter
{
public:
	typedef std::function<CommandResult(std::vector<std::string>)> CommandFunction;

	unsigned char registerKeyword(const std::string& keyword);
	unsigned char queryKeyword(const std::string& keyword);
	void registerCommand(const std::vector<std::string>& command, CommandFunction function);

	std::vector<CommandResult> interpretMulticommand(const std::string& command);
	CommandResult interpretCommand(const std::string& command);

private:
	uint32_t calcCommandIndex(const std::vector<std::string>& command);

	std::map<std::string, unsigned char> _keywordIdMap;
	std::map<uint32_t, CommandFunction> _commandFunctionMap;

	unsigned char _maxKeywordId = 1;
};

class VimStyleCommandLabel : public fei::Label
{
public:
	VimStyleCommandLabel();

	CommandInterpreter* getInterpreter();

	void inputChar(char c);
	void deleteChar();

	void executeCommand();
	void prevCommand();
	void nextCommand();

	void focus();
	void unfocus();

	bool isFocus() const;

	void setFontCache(fei::FontCache* fontCache);
	void setString(const std::string& str);
	void clearString();

private:
	std::string _command;
	std::vector<std::string> _history;
	int _historyIndex;
	fei::FontCache* _fontCache;
	CommandInterpreter _interpreter;

	static const std::set<char> _focusChar;

	bool _focus;
};

} // namespace fut

inline fut::CommandResult::CommandResult(fut::CommandResult::Type type, const std::string& result)
: _type(type),
  _result(result)
{
}

#endif // _VIMSTYLECOMMANDLABEL_H_
