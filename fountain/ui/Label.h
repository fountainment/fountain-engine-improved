#if !defined(_FEI_LABEL_H_)
#define _FEI_LABEL_H_

#include "font/FontCache.h"
#include "render/Image.h"
#include "render/RenderObj.h"

namespace fei {

class Label : public RenderObj
{
public:
	Label();

	void drawIt() override;

	void clearString();
	void setString(FontCache& fontCache, const std::vector<unsigned long>& str);
	void setString(FontCache& fontCache, const std::string& str);
	void addString(FontCache& fontCache, const std::vector<unsigned long>& str);
	void addString(FontCache& fontCache, const std::string& str);

	int getLength();

	void setCenterAligned(bool b);
	void setCenter(const Vec2& center);

private:
	int length;
	int height;
	std::vector<Image> charList;
	std::vector<int> advanceList;

	bool _centerAligned;
};

} // namespace fei

#endif // _FEI_LABEL_H_
