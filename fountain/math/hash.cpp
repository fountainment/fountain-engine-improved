#include "hash.h"

int fei::bkdrHash(const char* str)
{
	int seed = 131;
	int hash = 0;
	while (*str) {
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7fffffff);
}