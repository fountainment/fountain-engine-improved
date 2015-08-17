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

char* fei::readFileBuffer(const char* filename)
{
	std::FILE *fp = std::fopen(filename, "rb");
	long fSize;
	char *buffer;
	size_t result;
	if (fp) {
		std::fseek(fp, 0, SEEK_END);
		fSize = std::ftell(fp);
		std::rewind(fp);
		buffer = new char[fSize]; 
		result = std::fread(buffer, 1, fSize, fp);
		std::fclose(fp);
		if ((long)result != fSize) {
			std::fprintf(stderr, "FileUtil: \"%s\" reading error!\n", filename);
			return nullptr;
		}
	} else {
		std::fprintf(stderr, "FileUtil: \"%s\" file not exist!\n", filename);
		return nullptr;
	}
	return buffer;
}
