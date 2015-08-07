#include "Render.h"
#include "../base/basedef.h"
#include <GL/glew.h>

using fei::Render;

Render* Render::instance = nullptr;

Render* Render::getInstance()
{
	if (!instance) {
		instance = new Render();
	}
	return instance; 
}

Render::Render()
{
}

bool Render::init()
{
	if (_isLoad) return true;
	_isLoad = true;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		_isLoad = false;
	}
	return _isLoad;
}

