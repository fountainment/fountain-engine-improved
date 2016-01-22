#if !defined(_FEI_CODING_H_)
#define _FEI_CODING_H_

#include "base/basedef.h"

namespace fei {

std::vector<unsigned long> utf8ToUnicode(const std::string& str);
const std::string unicodeToUtf8(const std::vector<unsigned long>& str);

} // namespace fei

#endif // _FEI_CODING_H_
