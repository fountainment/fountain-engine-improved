#include "base/stringUtil.h"

const std::vector<std::string> fei::strSplit(const std::string& str, char delim)
{
	std::vector<std::string> elems;
	std::stringstream ss(str);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

const std::vector<std::string> fei::strSplit(const std::string& str)
{
	auto elems = fei::strSplit(str, ' ');
	std::vector<std::string> ret;
	for (auto str : elems) {
		if (str != fei::EmptyStr) {
			ret.push_back(str);
		}
	}
	return ret;
}
