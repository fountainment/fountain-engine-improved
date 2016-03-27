#ifndef _FEI_STRINGUTIL_H_
#define _FEI_STRINGUTIL_H_

#include "base/basedef.h"

namespace fei {

const std::vector<std::string> strSplit(const std::string& str, char delim);
const std::vector<std::string> strSplit(const std::string& str);

} // namesapce fei

#endif // _FEI_STRINGUTIL_H_
