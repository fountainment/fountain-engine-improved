#include "math/coding.h"

std::vector<unsigned long> fei::utf8ToUnicode(const std::string& str)
{
	const unsigned char rOne[] = {0x00, 0x01, 0x03, 0x07, 0x0f,
				      0x1f, 0x3f, 0x7f, 0xff};
	std::vector<unsigned long> ans;
	int length = str.length();
	int index = 0;
	while (index < length) {
		unsigned char ucTmp = (unsigned char)str[index];
		unsigned long ulTmp;
		int fz = 0;
		while (ucTmp & (1 << (7 - fz))) fz++;
		assert(fz != 1 && fz < 8);
		ulTmp = (unsigned long)(ucTmp & rOne[7 - fz]);
		for (int offset = 1; offset < fz; offset++) {
			ulTmp <<= 6;
			assert(index + offset < length);
			ulTmp |= (unsigned char)str[index + offset] & rOne[6];
		}
		ans.push_back(ulTmp);
		if (fz) {
			index += fz;
		} else {
			index++;
		}
	}
	return ans;
}
