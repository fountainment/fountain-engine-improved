_Pragma("once")

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

private:
	FT_Library library;

	static Font* instance;
};

}
