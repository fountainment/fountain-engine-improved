#include "RenderObj.h"
#include <GL/glew.h>

using fei::RenderObj;

RenderObj::RenderObj()
: _isAlpha(false),
  angle(0.0f),
  scale(1.0f),
  shaderProg(nullptr)
{
}

void RenderObj::setShader(fei::ShaderProgram* sp)
{
	shaderProg = sp;
}

void RenderObj::draw()
{
	if (shaderProg) shaderProg->use();
	if (_isAlpha) glEnable(GL_BLEND);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(pos.x, pos.y, 0);
	glScalef(scale, scale, scale);
	drawIt();
	glDisable(GL_BLEND);
	if (shaderProg) shaderProg->pop();
}

void RenderObj::drawIt()
{
}
