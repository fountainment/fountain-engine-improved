#ifndef _FEI_STRINGUTIL_H_
#define _FEI_STRINGUTIL_H_

#include "base/basedef.h"

namespace fei {

class Vec2;

const std::vector<std::string> strSplit(const std::string& str, char delim);
const std::vector<std::string> strSplit(const std::string& str);

double strToDouble(const std::string& str);
float strToFloat(const std::string& str);
int strToInt(const std::string& str);

const std::vector<fei::Vec2> strVecToVec2Vec(const std::vector<std::string>& strVec);

int strFormat(std::string& str, const char* format, ...);
const std::string strFormat(const char* format, ...);

} // namesapce fei

inline double fei::strToDouble(const std::string& str)
{
	return std::atof(str.c_str());
}

inline float fei::strToFloat(const std::string& str)
{
	return static_cast<float>(std::atof(str.c_str()));
}

inline int fei::strToInt(const std::string& str)
{
	return std::atoi(str.c_str());
}

#endif // _FEI_STRINGUTIL_H_
