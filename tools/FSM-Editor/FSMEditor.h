#if !defined(_FSMEDITOR_H_)
#define _FSMEDITOR_H_

#include "fountain.h"

class FSMEditor : public fei::Application
{
public:
	void engineSetting(fei::Engine* e) override;

	const static fei::Color& darkColor;
	const static fei::Color& brightColor;
	const static fei::Color& midColor;
	const static fei::Color& lightColor;
	const static fei::Color& lighterColor;
	const static fei::Color& selectColor;
	static fei::FontCache font20;
	static fei::FontCache font;
};

#endif // _FSMEDITOR_H_
