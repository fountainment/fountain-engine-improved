#ifndef _FEI_MODULEBASE_H_
#define _FEI_MODULEBASE_H_

namespace fei {
	
class ModuleBase
{
public:
	virtual ~ModuleBase();
	bool feiInit();
	virtual bool init();
	virtual void executeBeforeFrame();
	virtual void executeAfterFrame();
	void feiDestroy();
	virtual void destroy();
	bool isLoaded();

protected:
	ModuleBase();

private:
	bool _isLoaded;
};

} // namespace fei

#endif // _FEI_MODULEBASE_H_
