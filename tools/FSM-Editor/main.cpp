#include <fountain.h>

#include "FSMEditor.h"
#include "FSMEditorScene.h"

using namespace fei;

const Color& FSMEditor::darkColor = fei::Color::Black;
const Color& FSMEditor::brightColor = fei::Color::White;
const Color& FSMEditor::midColor = fei::Color("#333");
FontCache FSMEditor::font;

void FSMEditor::engineSetting(Engine* e)
{
	font.loadFont("res/font/wqy.ttc", 40);

	e->window->setFullscreen(true);
	e->window->setSamples(8);
	e->window->setTitle("FSM-Editor");
	e->window->sceneManager->gotoScene(new FSMEditorScene());
}

int main()
{
	FSMEditor fsmEditor;
	fsmEditor.run();
	return 0;
}
