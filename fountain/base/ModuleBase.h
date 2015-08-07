#if !defined(_FEI_MODULEBASE_H_)
#define _FEI_MODULEBASE_H_

namespace fei {
	
class ModuleBase
{
protected:
	ModuleBase();
	bool _isLoad;
public:
	virtual ~ModuleBase();
	virtual bool init();
	virtual void executeBeforeFrame();
	virtual void executeAfterFrame();
	virtual void destroy();
	bool isLoad();
};

}

#endif
