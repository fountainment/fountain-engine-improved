#include "render/RenderObj.h"

#include <GL/glew.h>

#include "anime/Anime.h"

using fei::RenderObj;

RenderObj::RenderObj()
: _hasAlpha(false),
  _isVisible(true),
  _useColor(true),
  _angle(0.0f),
  _scale(1.0f),
  _zPos(0.0f),
  _anchor(fei::Vec2::ZERO),
  _shaderProg(nullptr),
  _substitute(nullptr),
  _anime(nullptr)
{
}

RenderObj::~RenderObj()
{
}

void RenderObj::setShader(fei::ShaderProgram* sp)
{
	_shaderProg = sp;
}

void RenderObj::setSubstitute(RenderObj* sub)
{
	_substitute = sub;
}

void RenderObj::setAnime(fei::Anime* _animePtr)
{
	_anime = _animePtr;
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

void RenderObj::setUseColor(bool useColor)
{
	_useColor = useColor;
}

void RenderObj::setScale(float scl)
{
	_scale = scl;
}

void RenderObj::setAngle(float agl)
{
	_angle = agl;
}

void RenderObj::setAnchor(const fei::Vec2& acr)
{
	_anchor = acr;
}

void RenderObj::setZPos(float z)
{
	_zPos = z;
}

float RenderObj::getScale() const
{
	return _scale;
}

float RenderObj::getAngle() const
{
	return _angle;
}

const fei::Vec2 RenderObj::getAnchor() const
{
	return _anchor;
}

float RenderObj::getZPos() const
{
	return _zPos;
}

void RenderObj::roundAnchor()
{
	_anchor *= 2.0f;
	_anchor.round();
	_anchor *= 0.5f;
}

void RenderObj::moveAnchor(const fei::Vec2& v)
{
	_anchor.add(v);
}

void RenderObj::rotate(float dltAgl)
{
	_angle += dltAgl;
}

void RenderObj::matrixTransformBegin()
{
	glTranslatef(getPosition().x, getPosition().y, _zPos);
	if (_angle != 0.0f) {
		glRotatef(_angle, 0.0f, 0.0f, 1.0f);
	}
	glPushMatrix();
	if (_scale != 1.0f) {
		glScalef(_scale, _scale, _scale);
	}
}

void RenderObj::anchorTransform()
{
	glTranslatef(-_anchor.x, -_anchor.y, 0.0f);
}

void RenderObj::matrixTransformEnd()
{
	glPopMatrix();
}

void RenderObj::feiBasicUpdate()
{
	if (_anime) {
		_anime->feiObjectUpdate(this);
	}
}

void RenderObj::draw()
{
	if (_useColor) {
		_color.use();
	}
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
	if (_shaderProg && visible) {
		_shaderProg->push();
	}

	matrixTransformBegin();

	if (visible) {
		if (_substitute) {
			_substitute->anchorTransform();
			_substitute->drawIt();
		} else {
			anchorTransform();
			drawIt();
		}
	}

	matrixTransformEnd();

	if (_shaderProg && visible) {
		_shaderProg->pop();
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
	_color = c;
}

const fei::Color RenderObj::getColor() const
{
	return _color;
}
