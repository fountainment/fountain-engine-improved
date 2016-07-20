#include "VimStyleCommandLabel.h"

#include "base/stringUtil.h"

using fut::CommandResult;
using fut::CommandInterpreter;
using fut::VimStyleCommandLabel;

const CommandResult CommandResult::Ok = CommandResult(CommandResult::Type::OK, "Ok!");
const CommandResult CommandResult::Error = CommandResult(CommandResult::Type::ERROR, "Error!");

void CommandInterpreter::registerCommand(const std::vector<std::string>& command, CommandFunction function)
{
	auto commandIndex = calcCommandIndex(command);
	_commandFunctionMap[commandIndex] = function;
}

unsigned char CommandInterpreter::registerKeyword(const std::string& keyword)
{
	unsigned char ret = queryKeyword(keyword);
	if (ret == 0) {
		_maxKeywordId++;
		ret = _maxKeywordId;
		_keywordIdMap[keyword] = ret;
	}
	return ret;
}

unsigned char CommandInterpreter::queryKeyword(const std::string& keyword)
{
	auto it = _keywordIdMap.find(keyword);
	if (it == _keywordIdMap.end()) {
		return 0;
	}
	return it->second;
}

CommandResult CommandInterpreter::interpretCommand(const std::string& command)
{
	CommandResult ret;
	auto elements = fei::strSplit(command);
	std::vector<std::string> coms, args;
	bool commandPart = true;
	for (auto str : elements) {
		if (commandPart) {
			if (queryKeyword(str) != 0) {
				coms.push_back(str);
			} else {
				commandPart = false;
			}
		}
		if (!commandPart) {
			args.push_back(str);
		}
	}
	auto commandIndex = calcCommandIndex(coms);
	auto func = _commandFunctionMap[commandIndex];
	if (func != nullptr) {
		ret = func(args);
	} else {
		ret._type = CommandResult::Type::ERROR;
		ret._result = "Command not found!";
	}
	return ret;
}

uint32_t CommandInterpreter::calcCommandIndex(const std::vector<std::string>& command)
{
	uint32_t ret = 0U;
	for (auto keyword : command) {
		auto keywordIndex = registerKeyword(keyword);
		ret <<= 8;
		ret |= keywordIndex;
	}
	return ret;
}

const std::set<char> VimStyleCommandLabel::_focusChar = {':', '/', '%'};

VimStyleCommandLabel::VimStyleCommandLabel()
: _fontCache(nullptr),
  _focus(false)
{
}

CommandInterpreter* VimStyleCommandLabel::getInterpreter()
{
	return &_interpreter;
}

void VimStyleCommandLabel::inputChar(char c)
{
	if (!isFocus() && _focusChar.find(c) != _focusChar.end()) {
		focus();
	}
	if (_focus) {
		_command += c;
		if (_fontCache != nullptr) {
			setColor(fei::Color::White);
			setString(_command);
		}
	}
}

void VimStyleCommandLabel::deleteChar()
{
	if (_command != fei::EmptyStr) {
		_command.pop_back();
		setColor(fei::Color::White);
		setString(_command);
		if (_command == fei::EmptyStr) {
			unfocus();
		}
	}
}

void VimStyleCommandLabel::executeCommand()
{
	if (!isFocus()) {
		return;
	}
	auto result = _interpreter.interpretCommand(_command);
	_history.push_back(_command);
	_historyIndex = _history.size();
	_command = fei::EmptyStr;
	if (result._type == CommandResult::Type::OK) {
		setColor(fei::Color::White);
	} else {
		setColor(fei::Color::Red);
	}
	setString(result._result);
	unfocus();
}

void VimStyleCommandLabel::prevCommand()
{
	if (isFocus() && !_history.empty() && static_cast<int>(_historyIndex) > 0) {
		_historyIndex--;
		_command = _history[_historyIndex];
		setColor(fei::Color::White);
		setString(_command);
	}
}

void VimStyleCommandLabel::nextCommand()
{
	if (isFocus() && !_history.empty() && _historyIndex < static_cast<int>(_history.size()) - 1) {
		_historyIndex++;
		_command = _history[_historyIndex];
		setColor(fei::Color::White);
		setString(_command);
	}
}

void VimStyleCommandLabel::focus()
{
	_focus = true;
}

void VimStyleCommandLabel::unfocus()
{
	_focus = false;
}

bool VimStyleCommandLabel::isFocus() const
{
	return _focus;
}

void VimStyleCommandLabel::setFontCache(fei::FontCache* fontCache)
{
	_fontCache = fontCache;
}

void VimStyleCommandLabel::setString(const std::string& str)
{
	if (_fontCache != nullptr) {
		Label::setString(*_fontCache, str);
	}
}

void VimStyleCommandLabel::clearString()
{
	_command = fei::EmptyStr;
	setString(_command);
}