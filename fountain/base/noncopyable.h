#ifndef _FEI_NONCOPYABLE_H_
#define _FEI_NONCOPYABLE_H_

namespace fei {

class noncopyable
{
	protected:
		noncopyable() = default;
		~noncopyable() = default;
		noncopyable(const noncopyable&) = delete;
		const noncopyable& operator=(const noncopyable&) = delete;
};

} // namespace fei

#endif // _FEI_NONCOPYABLE_H_
