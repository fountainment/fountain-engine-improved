#include "math/hash.h"

int fei::bkdrHash(const std::string& str)
{
	int seed = 131;
	int hash = 0;
	for (auto character : str) {
		hash = hash * seed + character;
	}
	return (hash & 0x7fffffff);
}
