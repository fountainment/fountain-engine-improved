#if !defined(_FEI_LABEL_H_)
#define _FEI_LABEL_H_

#include "render/RenderObj.h"
#include "render/Image.h"
#include "font/FontCache.h"

namespace fei {

class Label : public RenderObj
{
public:
	Label();

	void drawIt() override;

	void setString(FontCache& fontCache, const std::vector<unsigned long>& str);
	void setString(FontCache& fontCache, const std::string& str);

	int getLength();

private:
	int length;
	std::vector<Image> charList;
	std::vector<int> advanceList;
};

}

#endif
