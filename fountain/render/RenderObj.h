#ifndef _FEI_RENDEROBJ_H_
#define _FEI_RENDEROBJ_H_

#include "base/NodeBase.h"
#include "render/Color.h"
#include "render/Shader.h"

namespace fei {

class Anime;
class RenderList;

class RenderObj : public fei::NodeBase
{
public:
	friend class RenderList;

	RenderObj();
	virtual ~RenderObj() = default;

	void matrixTransformBegin();
	void anchorTransform();
	void matrixTransformEnd();

	void animeUpdate();
	virtual void feiBasicUpdate() override;

	void draw();
	virtual void beforeDraw();
	virtual void afterDraw();
	virtual void drawIt();

	void setShader(ShaderProgram* sp);
	ShaderProgram* getShader();

	RenderList* getParent();
	void delFromParent();

	void setSubstitute(RenderObj* sub);
	RenderObj* getSubstitute();

	void setAnime(Anime* anime);
	Anime* getAnime();

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

private:
	void setParent(RenderList* parent);

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
	RenderList* _parent;
	RenderObj* _substitute;
	Anime* _anime;
};

} // namespace fei

inline fei::RenderObj::RenderObj()
: _hasAlpha(false),
  _isVisible(true),
  _useColor(true),
  _angle(0.0f),
  _scale(1.0f),
  _zPos(0.0f),
  _anchor(fei::Vec2::ZERO),
  _color(fei::Color::White),
  _shaderProg(nullptr),
  _parent(nullptr),
  _substitute(nullptr),
  _anime(nullptr)
{
}

#endif // _FEI_RENDEROBJ_H_
