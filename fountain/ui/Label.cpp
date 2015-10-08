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

void Label::setString(fei::FontCache& fontCache, const std::vector<unsigned long>& str)
{
	length = 0;
	for (auto charactor : str) {
		charList.push_back(fontCache.queryCharactor(charactor));
		int advance = fontCache.queryAdvance(charactor);
		advanceList.push_back(advance);
		length += advance;
	}
}

void Label::setString(fei::FontCache& fontCache, const std::string& str)
{
	auto unicodeStr = fei::utf8ToUnicode(str);
	setString(fontCache, unicodeStr);
}

int Label::getLength()
{
	return length;
}

void Label::setCenter(const fei::Vec2& center)
{
	setPosition(center - fei::Vec2(length, 0.0f) / 2.0f);
}
