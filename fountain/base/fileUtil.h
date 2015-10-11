#if !defined(_FEI_FILEUTIL_H_)
#define _FEI_FILEUTIL_H_

#include <string>

namespace fei {

bool isFileExist(const std::string& filename);
char* readFileBuffer(const std::string& filename);

}

#endif
