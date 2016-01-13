#if !defined(_FSMEDITOR_H_)
#define _FSMEDITOR_H_

class FSMEditor : public fei::Application
{
public:
	void engineSetting(fei::Engine* e) override;

	const static fei::Color& darkColor;
	const static fei::Color& brightColor;
	const static fei::Color& midColor;
	static fei::FontCache font;
};

#endif
