#include "ui/Label.h"

#include "math/coding.h"

using fei::Label;

Label::Label()
: _length(0),
  _height(0),
  _centerAligned(false)
{
	setHasAlpha(true);
}

void Label::drawIt()
{
	int size = _charList.size();
	assert(static_cast<int>(_advanceList.size()) == size);
	glTranslatef(-getAnchor().x, -getAnchor().y, 0.0f);
	for (int i = 0; i < size; i++) {
		_charList[i].draw();
		glTranslatef(static_cast<GLfloat>(_advanceList[i]), 0.0f, 0.0f);
	}
}

void Label::clearString()
{
	_length = 0;
	_charList.clear();
	_advanceList.clear();
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
		_charList.push_back(image);
		int advance = fontCache.queryAdvance(charactor);
		if (prev) {
			advance += fontCache.queryKerning(prev, charactor);
		}
		_advanceList.push_back(advance);
		_length += advance;
		prev = charactor;
	}
	if (_centerAligned) {
		setAnchor(Vec2(static_cast<float>(_length), 0.0f) / 2.0f);
	}
}

void Label::addString(fei::FontCache& fontCache, const std::string& str)
{
	auto unicodeStr = fei::utf8ToUnicode(str);
	addString(fontCache, unicodeStr);
}

int Label::getLength()
{
	return _length;
}

void Label::setCenterAligned(bool b)
{
	_centerAligned = b;
	if (_centerAligned) {
		setAnchor(fei::Vec2(static_cast<float>(_length), 0.0f) / 2.0f);
	} else {
		setAnchor(fei::Vec2::ZERO);
	}
}

void Label::setCenter(const fei::Vec2& center)
{
	if (_centerAligned) {
		setPosition(center);
	} else {
		setPosition(center - fei::Vec2(static_cast<float>(_length), 0.0f) / 2.0f);
	}
	//TODO: label center setting of y axis
}
