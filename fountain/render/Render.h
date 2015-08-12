#if !defined(_FEI_RENDER_H_)
#define _FEI_RENDER_H_

#include "base/ModuleBase.h"
#include "math/Rect.h"

namespace fei {

class Render : public fei::ModuleBase
{
public:
	bool init() override;

	void executeBeforeFrame() override;
	void executeAfterFrame() override;

	void setViewport(const Rect& viewport);

	static Render* getInstance();
private:
	Render();
	static Render* instance;
};

}

#endif
