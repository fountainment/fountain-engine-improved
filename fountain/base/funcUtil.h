#ifndef _FEI_FUNCUTIL_H_
#define _FEI_FUNCUTIL_H_

#include "base/basedef.h"

namespace fei {

template <class T>
inline std::function<void()> deleteFunc(T t)
{
	return [t](){delete t;};
}

template <class T>
inline std::function<void()> funcVector(std::vector<std::function<void()>> v)
{
	return [v](){for (auto f : v){f();}};
}

} // namespace fei

#endif // _FEI_FUNCUTIL_H_
