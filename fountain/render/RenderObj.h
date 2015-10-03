#if !defined(_FEI_RENDEROBJ_H_)
#define _FEI_RENDEROBJ_H_

#include "base/NodeBase.h"
#include "render/Color.h"
#include "render/Shader.h"

namespace fei {

class RenderObj : public fei::NodeBase
{
public:
	RenderObj();
	virtual ~RenderObj();

	virtual void init();
	virtual void destroy();
	virtual void update();

	virtual void feiInit();
	virtual void feiDestroy();
	virtual void feiUpdate();

	void matrixTransformBegin();
	void matrixTransformEnd();

	void draw();
	virtual void drawIt();

	void setShader(fei::ShaderProgram* sp);

	bool isAlpha() const;
	void setIsAlpha(bool alpha);

	bool isVisible() const;
	void setVisible(bool _isVisible);

	void hide();
	void show();

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
	bool _isAlpha;
	bool _isVisible;
	//int alphaFunc;
	float angle;
	float scale;
	float zPos;
	Vec2 anchor;
	Color color;
	ShaderProgram* shaderProg;
};

}

#endif
