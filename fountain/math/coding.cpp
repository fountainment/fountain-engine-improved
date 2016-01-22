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

const std::string fei::unicodeToUtf8(const std::vector<unsigned long>& str)
{
	std::string ans;
	const unsigned long prefix = 0x00000080, mask = 0x0000003f;
	for (auto ul : str) {
		if (ul <= 0x000007f) {
			ans += (char)ul;
		}
		else if (ul <= 0x000007ff) {
			ans += (char)(0x000000c0 | (ul >> 6));
			ans += (char)(prefix | (ul & mask));
		}
		else if (ul <= 0x0000ffff) {
			ans += (char)(0x000000e0 | (ul >> 12));
			ans += (char)(prefix | ((ul >> 6) & mask));
			ans += (char)(prefix | (ul & mask));
		}
		else if (ul <= 0x001fffff) {
			ans += (char)(0x000000f0 | (ul >> 18));
			ans += (char)(prefix | ((ul >> 12) & mask));
			ans += (char)(prefix | ((ul >> 6) & mask));
			ans += (char)(prefix | (ul & mask));
		}
		else if (ul <= 0x03ffffff) {
			ans += (char)(0x000000f8 | (ul >> 24));
			ans += (char)(prefix | ((ul >> 18) & mask));
			ans += (char)(prefix | ((ul >> 12) & mask));
			ans += (char)(prefix | ((ul >> 6) & mask));
			ans += (char)(prefix | (ul & mask));
		}
		else {
			ans += (char)(0x000000fc | (ul >> 30));
			ans += (char)(prefix | ((ul >> 24) & mask));
			ans += (char)(prefix | ((ul >> 18) & mask));
			ans += (char)(prefix | ((ul >> 12) & mask));
			ans += (char)(prefix | ((ul >> 6) & mask));
			ans += (char)(prefix | (ul & mask));
		}
	}
	return ans;
}
