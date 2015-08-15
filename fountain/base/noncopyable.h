#if !defined(_FEI_NONCOPYABLE_H_)
#define _FEI_NONCOPYABLE_H_

namespace fei {

class noncopyable
{
	protected:
		noncopyable() {}
		~noncopyable() {}
	private:
		noncopyable(const noncopyable&);
		const noncopyable& operator=(const noncopyable&);
};

}

#endif
