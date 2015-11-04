#include "Label.h"
#include "math/coding.h"

using fei::Label;

Label::Label()
: length(0)
{
	setHasAlpha(true);
}

void Label::drawIt()
{
	int size = charList.size();
	assert((int)advanceList.size() == size);
	for (int i = 0; i < size; i++) {
		charList[i].draw();
		glTranslatef((GLfloat)advanceList[i], 0.0f, 0.0f);
	}
}

void Label::clearString()
{
	length = 0;
	charList.clear();
	advanceList.clear();
}

void Label::setString(fei::FontCache& fontCache, const std::vector<unsigned long>& str)
{
	clearString();
	addString(fontCache, str);
}

void Label::setString(fei::FontCache& fontCache, const std::string& str)
{
	auto unicodeStr = fei::utf8ToUnicode(str);
	setString(fontCache, unicodeStr);
}

void Label::addString(fei::FontCache& fontCache, const std::vector<unsigned long>& str)
{
	unsigned long prev = 0;
	for (auto charactor : str) {
		auto image = fontCache.queryCharactor(charactor); 
		image.setUseColor(false);
		charList.push_back(image);
		int advance = fontCache.queryAdvance(charactor);
		if (prev) {
			advance += fontCache.queryKerning(prev, charactor);
		}
		advanceList.push_back(advance);
		length += advance;
		prev = charactor;
	}
}

void Label::addString(fei::FontCache& fontCache, const std::string& str)
{
	auto unicodeStr = fei::utf8ToUnicode(str);
	addString(fontCache, unicodeStr);
}

int Label::getLength()
{
	return length;
}

void Label::setCenter(const fei::Vec2& center)
{
	setPosition(center - fei::Vec2((float)length, 0.0f) / 2.0f);
	//TODO: label center setting of y axis
}
