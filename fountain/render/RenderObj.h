#ifndef _FEI_RENDEROBJ_H_
#define _FEI_RENDEROBJ_H_

#include "base/NodeBase.h"
#include "render/Color.h"
#include "render/Shader.h"

namespace fei {

class Anime;

class RenderObj : public fei::NodeBase
{
public:
	RenderObj();
	virtual ~RenderObj();

	void matrixTransformBegin();
	void anchorTransform();
	void matrixTransformEnd();

	virtual void feiBasicUpdate() override;

	void draw();
	virtual void beforeDraw();
	virtual void afterDraw();
	virtual void drawIt();

	void setShader(ShaderProgram* sp);

	void setSubstitute(RenderObj* sub);

	void setAnime(Anime* animePtr);

	bool hasAlpha() const;
	void setHasAlpha(bool hasAlpha);

	bool isVisible() const;
	void setVisible(bool _isVisible);

	void hide();
	void show();

	void setUseColor(bool useColor);

	void setScale(float scl);
	void setAngle(float agl);
	void setAnchor(const Vec2& acr);
	void setZPos(float z);

	float getScale() const;
	float getAngle() const;
	const Vec2 getAnchor() const;
	float getZPos() const;

	void roundAnchor();
	void moveAnchor(const Vec2& v);

	void rotate(float dltAgl);

	void setColor(const Color& c);
	void setColorAlpha(float alpha);
	const Color getColor() const;

protected:
	bool _hasAlpha;
	bool _isVisible;
	bool _useColor;
	//int _alphaFunc;
	float _angle;
	float _scale;
	float _zPos;
	Vec2 _anchor;
	Color _color;
	ShaderProgram* _shaderProg;
	RenderObj* _substitute;
	Anime* _anime;
};

} // namespace fei

#endif // _FEI_RENDEROBJ_H_
