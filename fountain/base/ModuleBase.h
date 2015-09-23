#if !defined(_FEI_MODULEBASE_H_)
#define _FEI_MODULEBASE_H_

namespace fei {
	
class ModuleBase
{
protected:
	ModuleBase();

public:
	virtual ~ModuleBase();
	bool feiInit();
	virtual bool init();
	virtual void executeBeforeFrame();
	virtual void executeAfterFrame();
	void feiDestroy();
	virtual void destroy();
	bool isLoaded();

private:
	bool _isLoaded;
};

}

#endif
