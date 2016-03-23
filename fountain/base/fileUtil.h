#ifndef _FEI_FILEUTIL_H_
#define _FEI_FILEUTIL_H_

#include <base/basedef.h>

namespace fei {

bool isFileExist(const std::string& filename);
char* readFileBuffer(const std::string& filename);

} // namespace fei

#endif // _FEI_FILEUTIL_H_
