#include "fileUtil.h"

bool fei::isFileExist(const std::string& filename)
{
	bool ans = false;
	auto fp = std::fopen(filename.c_str(), "r");
	if (fp) {
		ans = true;
		std::fclose(fp);
	}
	return ans;
}

char* fei::readFileBuffer(const std::string& filename)
{
	std::FILE *fp = std::fopen(filename.c_str(), "rb");
	long fSize;
	char *buffer;
	size_t result;
	if (fp) {
		std::fseek(fp, 0, SEEK_END);
		fSize = std::ftell(fp);
		std::rewind(fp);
		buffer = new char[fSize + 1];
		result = std::fread(buffer, 1, fSize, fp);
		buffer[fSize] = '\0';
		std::fclose(fp);
		if ((long)result != fSize) {
			std::fprintf(stderr, "FileUtil: \"%s\" reading error!\n", filename.c_str());
			return nullptr;
		}
	} else {
		std::fprintf(stderr, "FileUtil: \"%s\" file not exist!\n", filename.c_str());
		return nullptr;
	}
	return buffer;
}
