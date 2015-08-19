#include "Render.h"
#include "interface/Interface.h"
#include "base/basedef.h"
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
	if (!fei::Interface::getInstance()->init()) {
		_isLoad = false;
		return false;
	}
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		_isLoad = false;
	} else {
		std::printf("GLEW Version: %s\n", glewGetString(GLEW_VERSION));
		std::printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
		if (GLEW_VERSION_2_0) {
			std::printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
		} else {
			std::printf("Shader unsupported!\n");
		}
	}
	return _isLoad;
}

void Render::destroy()
{
	while (!shaderStack.empty()) {
		shaderStack.pop();
	}
}

void Render::executeBeforeFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
}

void Render::executeAfterFrame()
{
	glPopMatrix();
}

void Render::setViewport(const fei::Rect& viewport)
{
	glViewport(viewport.position.x, viewport.position.y,
			viewport.size.x, viewport.size.y);
}

void Render::pushShader(fei::ShaderProgram* shader)
{
	if (shaderStack.empty() || shaderStack.top() != shader) {
		shaderStack.push(shader);
		glUseProgram(shader->id);
	}
}

void Render::popShader(fei::ShaderProgram* shader)
{
	if (!shaderStack.empty() && shaderStack.top() == shader) {
		shaderStack.pop();
		if (shaderStack.empty()) {
			glUseProgram(0);
		} else {
			glUseProgram((shaderStack.top())->id);
		}
	}
}

fei::ShaderProgram* Render::getShaderProgram()
{
	if (!shaderStack.empty()) {
		return shaderStack.top();
	} else {
		return nullptr;
	}
}
