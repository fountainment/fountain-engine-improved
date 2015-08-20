#if !defined(_FEI_RENDER_H_)
#define _FEI_RENDER_H_

#include "base/basedef.h"
#include "base/ModuleBase.h"
#include "math/Vec2.h"
#include "math/Rect.h"
#include "Shader.h"

namespace fei {

class Render : public fei::ModuleBase
{
public:
	bool init() override;
	void destroy() override;

	void executeBeforeFrame() override;
	void executeAfterFrame() override;

	void setViewport(const Rect& viewport);

	void pushShader(ShaderProgram* shader);
	void popShader(ShaderProgram* shader);
	ShaderProgram* getShaderProgram();

	void bindTexture(GLuint tex);
	void drawTexQuad(const Vec2& size, GLfloat* texCoord = nullptr);

	static Render* getInstance();

private:
	Render();

	ShaderProgram basicShader;
	std::stack<ShaderProgram*> shaderStack;

	static Render* instance;
};

}

#endif
