#if !defined(_FEI_RENDEROBJ_H_)
#define _FEI_RENDEROBJ_H_

#include "base/NodeBase.h"
#include "render/Shader.h"

namespace fei {

class RenderObj : public fei::NodeBase
{
public:
	RenderObj();

	virtual void update();
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

	void rotate(float dltAgl);

protected:
	bool _isAlpha;
	bool _isVisible;
	//int alphaFunc;
	float angle;
	float scale;
	Vec2 anchor;
	ShaderProgram* shaderProg;
};

}

#endif
