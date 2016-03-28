#ifndef _TOOLS_COLLISIONEDITOR_H_
#define _TOOLS_COLLISIONEDITOR_H_

#include "fountain.h"
#include "util/VimStyleCommandLabel.h"

class EditorScene : public fei::Scene
{
public:
	virtual void init() override;
	virtual void update() override;

	void initUILayout();

	virtual void keyCallback(int key, int scancode, int action, int mods) override;
	virtual void charactorCallback(unsigned int codepoint) override;


private:
	fei::Camera _camera;
	fei::FontCache _fontCache;
	fut::VimStyleCommandLabel _commandLabel;
	fei::Texture _texture;
};

#endif // _TOOLS_COLLISIONEDITOR_H_
