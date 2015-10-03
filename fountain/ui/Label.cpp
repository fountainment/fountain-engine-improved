#include "Label.h"
#include "math/coding.h"

using fei::Label;

Label::Label()
: length(0)
{
	setIsAlpha(true);
}

void Label::drawIt()
{
	int size = charList.size();
	assert((int)advanceList.size() == size);
	for (int i = 0; i < size; i++) {
		charList[i].draw();
		glTranslatef(advanceList[i], 0.0f, 0.0f);
	}
}

void Label::setString(FontCache& fontCache, const std::vector<unsigned long>& str)
{
	length = 0;
	for (auto charactor : str) {
		charList.push_back(fontCache.queryCharactor(charactor));
		int advance = fontCache.queryAdvance(charactor);
		advanceList.push_back(advance);
		length += advance;
	}
}

void Label::setString(FontCache& fontCache, const std::string& str)
{
	auto unicodeStr = fei::utf8ToUnicode(str);
	setString(fontCache, unicodeStr);
}

int Label::getLength()
{
	return length;
}
