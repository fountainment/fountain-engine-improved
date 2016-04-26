#include "FountainShader.h"

using fei::Light;
using fei::LightManager;
using fei::FountainShader;

Light::Light(int* type, fei::Vec3* position, fei::Vec3* direction, fei::Vec4* color, float* radius)
: _type(type),
  _position(position),
  _direction(direction),
  _color(color),
  _radius(radius)
{
}

int Light::getType()
{
	return *_type;
}

const fei::Vec3 Light::getPosition()
{
	return *_position;
}

const fei::Vec3 Light::getDirection()
{
	return *_direction;
}

const fei::Vec4 Light::getColor()
{
	return *_color;
}

float Light::getIntensity()
{
	return _color->w;
}

float Light::getRadius()
{
	return *_radius;
}

void Light::setType(int type)
{
	*_type = type;
}

void Light::setPosition(const fei::Vec3& v)
{
	*_position = v;
}

void Light::setDirection(const fei::Vec3& v)
{
	*_direction = v;
}

void Light::setColor(const fei::Vec3& color)
{
	*_color = fei::Vec4(color, _color->w);
}
void Light::setColor(const fei::Vec4& color)
{
	*_color = color;
}

void Light::setIntensity(float intensity)
{
	_color->w = intensity;
}

void Light::setRadius(float radius)
{
	*_radius = radius;
}

void Light::move(const fei::Vec2& v)
{
	*_position += fei::Vec3(v, 0.0f);
}

void Light::move(const fei::Vec3& v)
{
	*_position += v;
}

LightManager::LightManager()
{
	_lightNum = 0;
	for (int i = 0; i < MAX_LIGHT_NUM; i++) {
		_light[i]._type = _lightType + i;
		_light[i]._position = _lightPosition + i;
		_light[i]._direction = _lightDirection + i;
		_light[i]._color = _lightColor + i;
		_light[i]._radius = _lightRadius + i;
	}
	for (int i = 0; i < MAX_LIGHT_NUM; i++) {
		_light[i].setType(Light::POINT_LIGHT);
		_light[i].setPosition(Vec3(0.0f, 0.0f, 50.0f));
		_light[i].setDirection(Vec3::YUP);
		_light[i].setColor(Vec3::ONE);
		_light[i].setIntensity(0.0f);
		_light[i].setRadius(100.0f);
	}
}

Light* LightManager::getLight(int index)
{
	//TODO: assert index < MAX_LIGHT_NUM
	return _light + index;
}

void LightManager::setLightNum(int num)
{
	_lightNum = num;
}

FountainShader::FountainShader()
{
}

void FountainShader::beforeLink()
{
	bindAllFragDataLocation();
}

void FountainShader::afterLink()
{
	cacheAllUniformLocation();
	setDefaultVariableValue();
}

void FountainShader::bindAllFragDataLocation()
{
	bindFragDataLocation(0, "feiColorOutput");
	bindFragDataLocation(1, "feiEmitOutput");
}

void FountainShader::cacheAllUniformLocation()
{
	_renderMode = getUniformLocation("feiRenderMode");
	_mouse = getUniformLocation("feiMouse");
	_time = getUniformLocation("feiTime");
	_viewCoord = getUniformLocation("feiViewCoord");

	_emitTex = getUniformLocation("feiEmitTex");
	_normalTex = getUniformLocation("feiNormalTex");
	_cullTex = getUniformLocation("feiCullTex");

	_useEmitTex = getUniformLocation("feiUseEmitTex");
	_useNormalTex = getUniformLocation("feiUseNormalTex");
	_useCullTex = getUniformLocation("feiUseCullTex");
	_useLight = getUniformLocation("feiUseLight");

	_kd = getUniformLocation("feiKd");
	_ks = getUniformLocation("feiKs");
	_smoothness = getUniformLocation("feiSmoothness");
	_emitValue = getUniformLocation("feiEmitValue");
	_emitAllValue = getUniformLocation("feiEmitAllValue");
	_normalValue = getUniformLocation("feiNormalValue");

	_blurRadius = getUniformLocation("feiBlurRadius");
	_sampleNum = getUniformLocation("feiSampleNum");

	_lw = getUniformLocation("feiLw");
	_lwhite = getUniformLocation("feiLwhite");

	_lightNum = getUniformLocation("feiLightNum");
	_lightType = getUniformLocation("feiLightType");
	_lightPosition = getUniformLocation("feiLightPos");
	_lightDirection = getUniformLocation("feiLightDirection");
	_lightColor = getUniformLocation("feiLightColor");
	_lightRadius = getUniformLocation("feiLightRadius");
}

void FountainShader::setDefaultVariableValue()
{
	setUniform(_emitTex, EMIT_TEX);
	setUniform(_normalTex, NORMAL_TEX);
	setUniform(_cullTex, CULL_TEX);

	setRenderMode(RENDER_PLAIN);
	setMouse(fei::Vec2::ZERO);
	setTime(0.0f);
	setViewCoord(fei::Vec3::ZERO);

	setUseEmitTex(false);
	setUseNormalTex(false);
	setUseCullTex(false);

	setUseLight(false);

	setKd(fei::Vec3::ONE);
	setKs(fei::Vec3::ZERO);
	setSmoothness(0.0f);
	setEmitValue(1.0f);
	setEmitAllValue(0.0f);
	setNormalValue(fei::Vec3::ZUP);

	setBlurRadius(30.0f);
	setSampleNum(10.0f);

	setLw(1.0f);
	setLwhite(100.0f);
}

LightManager* FountainShader::getLightManager()
{
	return &_lightManager;
}

void FountainShader::setRenderMode(int renderMode)
{
	setUniform(_renderMode, renderMode);
}

void FountainShader::setMouse(const fei::Vec2& v)
{
	setUniform(_mouse, v);
}

void FountainShader::setTime(float t)
{
	setUniform(_time, t);
}

void FountainShader::setViewCoord(const fei::Vec3& v)
{
	setUniform(_viewCoord, v);
}

void FountainShader::setUseEmitTex(bool useEmitTex)
{
	setUniform(_useEmitTex, useEmitTex);
}

void FountainShader::setUseNormalTex(bool useNormalTex)
{
	setUniform(_useNormalTex, useNormalTex);
}

void FountainShader::setUseCullTex(bool useCullTex)
{
	setUniform(_useCullTex, useCullTex);
}

void FountainShader::setUseLight(bool useLight)
{
	setUniform(_useLight, useLight);
}

void FountainShader::setKd(const fei::Vec3& kd)
{
	setUniform(_kd, kd);
}

void FountainShader::setKs(const fei::Vec3& ks)
{
	setUniform(_ks, ks);
}

void FountainShader::setSmoothness(float m)
{
	setUniform(_smoothness, m);
}

void FountainShader::setEmitValue(float emitValue)
{
	setUniform(_emitValue, emitValue);
}

void FountainShader::setEmitAllValue(float emitAllValue)
{
	setUniform(_emitAllValue, emitAllValue);
}

void FountainShader::setNormalValue(const fei::Vec3& normalValue)
{
	setUniform(_normalValue, normalValue);
}

void FountainShader::setBlurRadius(float blurRadius)
{
	setUniform(_blurRadius, blurRadius);
}

void FountainShader::setSampleNum(float sampleNum)
{
	setUniform(_sampleNum, sampleNum);
}

void FountainShader::setLw(float lw)
{
	setUniform(_lw, lw);
}

void FountainShader::setLwhite(float lwhite)
{
	setUniform(_lwhite, lwhite);
}

void FountainShader::setLightData()
{
	int lightNum = _lightManager._lightNum;
	setUniform(_lightNum, lightNum);
	setUniform(_lightType, _lightManager._lightType, lightNum);
	setUniform(_lightPosition, _lightManager._lightPosition, lightNum);
	setUniform(_lightDirection, _lightManager._lightDirection, lightNum);
	setUniform(_lightColor, _lightManager._lightColor, lightNum);
	setUniform(_lightRadius, _lightManager._lightRadius, lightNum);
}
