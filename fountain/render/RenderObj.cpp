#include "RenderObj.h"
#include <GL/glew.h>

using fei::RenderObj;

RenderObj::RenderObj()
: _hasAlpha(false),
  _isVisible(true),
  angle(0.0f),
  scale(1.0f),
  zPos(0.0f),
  anchor(fei::Vec2::ZERO),
  shaderProg(nullptr)
{
}

RenderObj::~RenderObj()
{
}

void RenderObj::setShader(fei::ShaderProgram* sp)
{
	shaderProg = sp;
}

void RenderObj::setSubstitute(RenderObj* sub)
{
	substitute = sub;
}

bool RenderObj::hasAlpha() const
{
	return _hasAlpha;
}

void RenderObj::setHasAlpha(bool hasAlpha)
{
	_hasAlpha = hasAlpha;
}

bool RenderObj::isVisible() const
{
	return _isVisible;
}

void RenderObj::setVisible(bool visible)
{
	_isVisible = visible;
}

void RenderObj::hide()
{
	setVisible(false);
}

void RenderObj::show()
{
	setVisible(true);
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

void RenderObj::setZPos(float z)
{
	zPos = z;
}

float RenderObj::getScale() const
{
	return scale;
}

float RenderObj::getAngle() const
{
	return angle;
}

const fei::Vec2 RenderObj::getAnchor() const
{
	return anchor;
}

float RenderObj::getZPos() const
{
	return zPos;
}

void RenderObj::rotate(float dltAgl)
{
	angle += dltAgl;
}

void RenderObj::matrixTransformBegin()
{
	glTranslatef(pos.x, pos.y, zPos);
	if (angle != 0.0f) {
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
	}
	glPushMatrix();
	if (scale != 1.0f) {
		glScalef(scale, scale, scale);
	}
	glTranslatef(-anchor.x, -anchor.y, 0.0f);
}

void RenderObj::matrixTransformEnd()
{
	glPopMatrix();
}

void RenderObj::draw()
{
	color.use();
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	if (_hasAlpha) {
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	} else {
		glDepthFunc(GL_LESS);
	}

	bool visible = isVisible();
	if (shaderProg && visible) {
		shaderProg->push();
	}

	matrixTransformBegin();

	if (visible) {
		if (substitute) {
			drawIt();
		} else {
			drawIt();
		}
	}

	matrixTransformEnd();

	if (shaderProg && visible) {
		shaderProg->pop();
	}

	glDisable(GL_DEPTH_TEST);
	if (_hasAlpha) {
		glDisable(GL_BLEND);
	}
}

void RenderObj::drawIt()
{
}

void RenderObj::setColor(const fei::Color& c)
{
	color = c;
}

const fei::Color RenderObj::getColor() const
{
	return color;
}
