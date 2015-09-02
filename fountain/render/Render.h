#if !defined(_FEI_RENDER_H_)
#define _FEI_RENDER_H_

#include "base/basedef.h"
#include "base/ModuleBase.h"
#include "math/Vec2.h"
#include "math/Rect.h"
#include "math/Shape.h"
#include "Shader.h"
#include <GL/glew.h>

namespace fei {

class Render : public fei::ModuleBase
{
public:
	bool init() override;
	void destroy() override;

	void executeBeforeFrame() override;
	void executeAfterFrame() override;

	void setViewport(const Rect& viewport);
	const Rect getViewport();

	void pushShader(ShaderProgram* shader);
	void popShader(ShaderProgram* shader);
	ShaderProgram* getShaderProgram();

	void registTexture(const char* filename, GLuint id);
	void deleteTexture(GLuint id);
	int queryTexture(const char* filename);
	void registTexSize(GLuint id, const Vec2& s);
	const Vec2 queryTexSize(GLuint id);
	void addRefTexture(GLuint id);
	void releaseTexture(GLuint id);
	void deleteUnusedTexture();

	void bindTexture(GLuint tex);
	void disableTexture();
	void drawTexQuad(const Vec2& size, GLfloat* texCoord = nullptr);
	void drawShape(const Shape* shape);

	static Render* getInstance();

private:
	Render();

	ShaderProgram basicShader;
	std::stack<ShaderProgram*> shaderStack;

	std::map<int, GLuint> fileTextureMap;
	std::map<GLuint, Vec2> textureSizeMap;
	std::map<GLuint, int> textureRCMap;

	static Render *instance;
};

}

#endif
