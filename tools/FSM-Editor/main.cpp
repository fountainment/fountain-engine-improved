#include <fountain.h>

#include "FSMEditor.h"
#include "FSMEditorScene.h"

using namespace fei;

const Color& FSMEditor::darkColor = fei::Color::Black;
const Color& FSMEditor::brightColor = fei::Color::White;
const Color& FSMEditor::midColor = fei::Color("#333");
const Color& FSMEditor::lightColor = fei::Color("#09C");
const Color& FSMEditor::lighterColor = fei::Color("#0AD");
FontCache FSMEditor::font20;
FontCache FSMEditor::font;

void FSMEditor::engineSetting(Engine* e)
{
	font20.loadFont("res/font/wqy.ttc", 20);
	font.loadFont("res/font/wqy.ttc", 40);

	auto tex = font.getCacheTexture();
	tex.setMagFilter(GL_LINEAR);
	auto tex20 = font20.getCacheTexture();
	tex20.setMagFilter(GL_LINEAR);

	//e->window->setFullscreen(true);
	e->window->setSize(800, 600);
	e->window->setSamples(8);
	e->window->setTitle("FSM-Editor");
	e->window->getSceneManager()->gotoScene(new FSMEditorScene());
}

int main()
{
	FSMEditor fsmEditor;
	fsmEditor.run();
	return 0;
}
