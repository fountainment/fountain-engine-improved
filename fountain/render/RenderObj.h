#if !defined(_FEI_RENDEROBJ_H_)
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
	void matrixTransformEnd();

	void feiUpdate() override;

	void draw();
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

	void rotate(float dltAgl);

	void setColor(const Color& c);
	const Color getColor() const;

protected:
	bool _hasAlpha;
	bool _isVisible;
	bool _useColor;
	//int alphaFunc;
	float angle;
	float scale;
	float zPos;
	Vec2 anchor;
	Color color;
	ShaderProgram* shaderProg;
	RenderObj* substitute;
	Anime* anime;
};

}

#endif
