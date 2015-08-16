#include "fileUtil.h"
#include "base/basedef.h"

bool fei::isFileExist(const char* filename)
{
	bool ans = false;
	auto fp = std::fopen(filename, "r");
	if (fp) {
		ans = true;
		std::fclose(fp);
	}
	return ans;
}
