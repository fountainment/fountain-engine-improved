#include "random.h"

#include "base/basedef.h"

float fei::random()
{
	return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
}

float fei::randRangef(float l, float r)
{
	//TODO: assert l <= r
	float ret = fei::random();
	ret *= r - l;
	ret += l;
	return ret;
}

int fei::randRangei(int l, int r)
{
	//TODO: assert l <= r
	int ret = std::rand();
	ret %= r - l + 1;
	ret += l;
	return ret;
}
