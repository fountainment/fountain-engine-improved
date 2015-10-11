#include "hash.h"

int fei::bkdrHash(const std::string& str)
{
	int seed = 131;
	int hash = 0;
	for (auto charactor : str) {
		hash = hash * seed + charactor;
	}
	return (hash & 0x7fffffff);
}