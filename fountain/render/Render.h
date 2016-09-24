#ifndef _FEI_RENDER_H_
#define _FEI_RENDER_H_

#include <glad/glad.h>

#include "base/basedef.h"
#include "base/ModuleBase.h"
#include "math/Rect.h"
#include "math/Shape.h"
#include "math/Vec2.h"
#include "math/Vec4.h"
#include "render/Camera.h"
#include "render/Color.h"
#include "render/RenderObj.h"
#include "render/RenderTarget.h"
#include "render/Shader.h"

namespace fei {

class Render : public fei::ModuleBase
{
public:
	bool init() override;
	void destroy() override;

	void executeBeforeFrame() override;
	void executeAfterFrame() override;

	void clearBuffer();
	void initViewport();
	void initMatrix();
	void initShader();

	void pushShader(ShaderProgram* shader);
	void popShader(ShaderProgram* shader);
	ShaderProgram* getShaderProgram();

	void registTexture(const std::string& filename, GLuint id);
	void deleteTexture(GLuint id);
	int queryTexture(const std::string& filename);
	void registTexSize(GLuint id, const Vec2& s);
	const Vec2 queryTexSize(GLuint id);
	void addRefTexture(GLuint id);
	void releaseTexture(GLuint id);
	void deleteUnusedTexture();

	void bindTexture(GLuint tex);
	void disableTexture();

	void setCurrentCamera(Camera* camera);
	Camera* getCurrentCamera();

	void setCurrentRenderTarget(RenderTarget* renderTarget);
	RenderTarget* getCurrentRenderTarget();

	void setViewport(const Rect& viewport);
	const Rect getViewport();
	void setClearColor(const Vec4* color);

	int getMaxTextureSize();

	static void drawArray2f(const GLfloat* vertex, GLint first, GLsizei count, GLenum mode);

	static void drawLine(const Vec2& pa, const Vec2& pb);
	static void drawRect(const Vec2& size);
	static void drawRect(const Rect& rect);
	static void drawQuad(const Vec2& size);
	static void drawQuadDS(const Vec2& size);

	static void drawTexRect(const Vec2& size);
	static void drawTexRect(const Rect& rect);
	static void drawTexQuad(const Vec2& size);
	static void drawTexQuadDS(const Vec2& size);

	static void drawTexRect(const Vec2& size, GLfloat* texCoord);
	static void drawTexRect(const Rect& rect, GLfloat* texCoord);
	static void drawTexQuad(const Vec2& size, GLfloat* texCoord);
	static void drawTexQuadDS(const Vec2& size, GLfloat* texCoord);

	static void drawShape(const Shape* shape);

	static void IndependentDraw(RenderObj* rObj);

	static void useColor(const Vec4* color);

	static Render* getInstance();

private:
	Render();

	Camera* _currentCamera;
	RenderTarget* _currentRenderTarget;

	ShaderProgram _basicShader;
	std::stack<ShaderProgram*> _shaderStack;

	std::map<int, GLuint> _fileTextureMap;
	std::map<GLuint, Vec2> _textureSizeMap;
	std::map<GLuint, int> _textureRCMap;

	Rect _viewport;
	int _maxTexSize;

	static const GLfloat stripTexCoord_[8];

	static Render *instance_;
};

inline void Render::drawArray2f(const GLfloat* vertex, GLint first, GLsizei count, GLenum mode)
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertex);
	glDrawArrays(mode, first, count);
	glDisableVertexAttribArray(0);
}

inline void Render::drawLine(const fei::Vec2& pa, const fei::Vec2& pb)
{
	GLfloat vertex[] = {pa.x, pa.y, pb.x, pb.y};
	drawArray2f(vertex, 0, 2, GL_LINES);
}

inline void Render::drawRect(const fei::Vec2& size)
{
	GLfloat vertex[] = {0.0f, size.y, 0.0f, 0.0f, size.x, size.y, size.x, 0.0f};
	drawArray2f(vertex, 0, 4, GL_TRIANGLE_STRIP);
}

inline void Render::drawRect(const fei::Rect& rect)
{
	GLfloat vertex[8];
	rect.getStripCoord(vertex);
	drawArray2f(vertex, 0, 4, GL_TRIANGLE_STRIP);
}

inline void Render::drawQuad(const fei::Vec2& size)
{
	GLfloat w2 = size.x * 0.5f;
	GLfloat h2 = size.y * 0.5f;
	GLfloat vertex[] = {-w2, h2, -w2, -h2, w2, h2, w2, -h2};
	drawArray2f(vertex, 0, 4, GL_TRIANGLE_STRIP);
}

inline void Render::drawQuadDS(const fei::Vec2& size)
{
	GLfloat w2 = size.x;
	GLfloat h2 = size.y;
	GLfloat vertex[] = {-w2, h2, -w2, -h2, w2, h2, w2, -h2};
	drawArray2f(vertex, 0, 4, GL_TRIANGLE_STRIP);
}

inline void Render::drawTexRect(const fei::Vec2& size)
{
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, stripTexCoord_);
	drawRect(size);
	glDisableVertexAttribArray(2);
}

inline void Render::drawTexRect(const fei::Rect& rect)
{
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, stripTexCoord_);
	drawRect(rect);
	glDisableVertexAttribArray(2);
}

inline void Render::drawTexQuad(const fei::Vec2& size)
{
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, stripTexCoord_);
	drawQuad(size);
	glDisableVertexAttribArray(2);
}

inline void Render::drawTexQuadDS(const fei::Vec2& size)
{
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, stripTexCoord_);
	drawQuadDS(size);
	glDisableVertexAttribArray(2);
}

inline void Render::drawTexRect(const fei::Vec2& size, GLfloat* texCoord)
{
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, texCoord);
	drawRect(size);
	glDisableVertexAttribArray(2);
}

inline void Render::drawTexRect(const fei::Rect& rect, GLfloat* texCoord)
{
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, texCoord);
	drawRect(rect);
	glDisableVertexAttribArray(2);
}

inline void Render::drawTexQuad(const fei::Vec2& size, GLfloat* texCoord)
{
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, texCoord);
	drawQuad(size);
	glDisableVertexAttribArray(2);
}

inline void Render::drawTexQuadDS(const fei::Vec2& size, GLfloat* texCoord)
{
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, texCoord);
	drawQuadDS(size);
	glDisableVertexAttribArray(2);
}

inline void Render::IndependentDraw(fei::RenderObj* rObj)
{
	glPushMatrix();
	rObj->draw();
	glPopMatrix();
}

} // namespace fei

#endif // _FEI_RENDER_H_
