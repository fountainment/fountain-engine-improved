#ifndef _FEI_FONT_H_
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

	FT_Library* getLibrary();

private:
	FT_Library _library;

	static Font* instance_;
};

} // namespace fei

inline FT_Library* fei::Font::getLibrary()
{
	return &_library;
}

#endif // _FEI_FONT_H_
