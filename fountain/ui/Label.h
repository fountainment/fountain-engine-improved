#ifndef _FEI_LABEL_H_
#define _FEI_LABEL_H_

#include "font/FontCache.h"
#include "render/Image.h"
#include "render/RenderObj.h"

namespace fei {

class Label : public RenderObj
{
public:
	Label();

	virtual void drawIt() override;

	void clearString();
	void setString(FontCache& fontCache, const std::vector<unsigned long>& str);
	void setString(FontCache& fontCache, const std::string& str);
	void addString(FontCache& fontCache, const std::vector<unsigned long>& str);
	void addString(FontCache& fontCache, const std::string& str);

	int getLength();

	void setCenterAligned(bool b);
	void setCenter(const Vec2& center);

private:
	int _length;
	int _height;
	std::vector<Image> _charList;
	std::vector<int> _advanceList;

	bool _centerAligned;
};

} // namespace fei

#endif // _FEI_LABEL_H_
