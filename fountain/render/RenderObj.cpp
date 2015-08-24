#include "RenderObj.h"
#include <GL/glew.h>

using fei::RenderObj;

RenderObj::RenderObj()
: _isAlpha(false),
  angle(0.0f),
  scale(1.0f),
  anchor(fei::Vec2(0.0f)),
  shaderProg(nullptr)
{
}

void RenderObj::setShader(fei::ShaderProgram* sp)
{
	shaderProg = sp;
}

bool RenderObj::isAlpha() const
{
	return _isAlpha;
}

void RenderObj::setIsAlpha(bool alpha)
{
	_isAlpha = alpha;
}

void RenderObj::setScale(float scl)
{
	scale = scl;
}

void RenderObj::setAngle(float agl)
{
	angle = agl;
}

void RenderObj::setAnchor(const fei::Vec2& acr)
{
	anchor = acr;
}

void RenderObj::rotate(float dltAgl)
{
	angle += dltAgl;
}

void RenderObj::update()
{
}

void RenderObj::draw()
{
	if (shaderProg) {
		shaderProg->push();
	}
	if (_isAlpha) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glScalef(scale, scale, scale);
	glTranslatef(-anchor.x, -anchor.y, 0.0f);
	drawIt();
	if (_isAlpha) {
		glDisable(GL_BLEND);
	}
	if (shaderProg) {
		shaderProg->pop();
	}
}

void RenderObj::drawIt()
{
}
