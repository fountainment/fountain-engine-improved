#if !defined(_FEI_FONT_H_)
#define _FEI_FONT_H_

#include <ft2build.h>
#include FT_FREETYPE_H

#include "base/basedef.h"
#include "base/ModuleBase.h"

namespace fei {

class Font : public fei::ModuleBase
{
public:
	static Font* getInstance();

	bool init() override;
	void destroy() override;

	FT_Library library;

private:
	static Font* instance;
};

} // namespace fei

#endif // _FEI_FONT_H_
