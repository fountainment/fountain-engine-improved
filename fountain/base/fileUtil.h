#if !defined(_FEI_FILEUTIL_H_)
#define _FEI_FILEUTIL_H_

namespace fei {

bool isFileExist(const char* filename);
char* readFileBuffer(const char* filename);

}

#endif
