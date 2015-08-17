#if !defined(_FEI_RENDEROBJ_H_)
#define _FEI_RENDEROBJ_H_

#include "base/NodeBase.h"
#include "render/Shader.h"

namespace fei {

class RenderObj : public fei::NodeBase
{
public:
	RenderObj();
	void draw();
	virtual void drawIt();
	void setShader(fei::ShaderProgram* sp);
protected:
	bool _isAlpha;
	//int alphaFunc;
	float angle;
	float scale;
	fei::ShaderProgram* shaderProg;
};

}

#endif
