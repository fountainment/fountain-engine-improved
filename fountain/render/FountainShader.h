#ifndef _RENDER_FOUNTAIN_SHADER_H_
#define _RENDER_FOUNTAIN_SHADER_H_

#include <glad/glad.h>

#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
#include "render/Shader.h"

namespace fei {

class LightManager;

class Light
{
public:
	friend class LightManager;

	int getType();
	const Vec3 getPosition();
	const Vec3 getDirection();
	const Vec4 getColor();
	float getIntensity();
	float getRadius();

	void setType(int type);
	void setPosition(const Vec3& v);
	void setDirection(const Vec3& v);
	void setColor(const Vec3& color);
	void setColor(const Vec4& color);
	void setIntensity(float intensity);
	void setRadius(float radius);

	void move(const Vec2& v);
	void move(const Vec3& v);

	static constexpr int RENDER_PLAIN = 0;
	static constexpr int RENDER_BLUR = 1;
	static constexpr int RENDER_BASIC = 2;
	static constexpr int RENDER_HDR = 3;
	static constexpr int RENDER_FINAL = 4;

	static constexpr int POINT_LIGHT = 0;
	static constexpr int DIRECTIONAL_LIGHT = 1;
	static constexpr int SPOT_LIGHT = 2;

private:
	Light() = default;
	Light(int* type, Vec3* position, Vec3* direction, Vec4* color, float* radius);

	int* _type;
	Vec3* _position;
	Vec3* _direction;
	Vec4* _color;
	float* _radius;
};

class LightManager
{
public:
	friend class FountainShader;

	Light* getLight(int index);
	void setLightNum(int num);

	static const int MAX_LIGHT_NUM = 64;

private:
	LightManager();

	Light _light[MAX_LIGHT_NUM];
	int _lightNum;
	int _lightType[MAX_LIGHT_NUM];
	Vec3 _lightPosition[MAX_LIGHT_NUM];
	Vec3 _lightDirection[MAX_LIGHT_NUM];
	Vec4 _lightColor[MAX_LIGHT_NUM];
	float _lightRadius[MAX_LIGHT_NUM];
};

class FountainShader : public fei::ShaderProgram
{
public:
	FountainShader();

	virtual void beforeLink() override;
	virtual void afterLink() override;

	LightManager* getLightManager();

	void setRenderMode(int renderMode);
	void setMouse(const Vec2& v);
	void setTime(float t);
	void setViewCoord(const Vec3& v);

	void setUseEmitTex(bool useEmitTex);
	void setUseNormalTex(bool useNormalTex);
	void setUseCullTex(bool useCullTex);

	void setUseLight(bool useLight);

	void setKd(const Vec3& kd);
	void setKs(const Vec3& ks);
	void setSmoothness(float m);
	void setEmitValue(float emitValue);
	void setEmitAllValue(float emitAllValue);
	void setNormalValue(const Vec3& normalValue);

	void setBlurRadius(float blurRadius);
	void setSampleNum(float sampleNum);

	void setLw(float lw);
	void setLwhite(float lwhite);

	void setLightData();

	void loadDefault();

	static const int RENDER_PLAIN = 0;
	static const int RENDER_BLUR = 1;
	static const int RENDER_BASIC = 2;
	static const int RENDER_HDR = 3;
	static const int RENDER_FINAL = 4;

	static const int EMIT_TEX = 1;
	static const int NORMAL_TEX = 2;
	static const int CULL_TEX = 3;

	static const int POINT_LIGHT = 0;
	static const int DIRECTIONAL_LIGHT = 1;
	static const int SPOT_LIGHT = 2;

private:
	void bindAllFragDataLocation();
	void cacheAllUniformLocation();
	void setDefaultVariableValue();

	//Basic
	GLint _renderMode;
	GLint _mouse;
	GLint _time;
	GLint _viewCoord;

	//Texture
	GLint _emitTex;
	GLint _normalTex;
	GLint _cullTex;

	//Switch
	GLint _useEmitTex;
	GLint _useNormalTex;
	GLint _useCullTex;
	GLint _useLight;

	//Material
	GLint _kd;
	GLint _ks;
	GLint _smoothness;
	GLint _emitValue;
	GLint _emitAllValue;
	GLint _normalValue;

	//Blur
	GLint _blurRadius;
	GLint _sampleNum;

	//HDR
	GLint _lw;
	GLint _lwhite;

	//Light Source
	GLint _lightNum;
	GLint _lightType;
	GLint _lightPosition;
	GLint _lightDirection;
	GLint _lightColor;
	GLint _lightRadius;

	LightManager _lightManager;

	static const GLchar *defaultVert_;
	static const GLchar *defaultFrag_;
};

}

#endif // _RENDER_FOUNTAIN_SHADER_H_
