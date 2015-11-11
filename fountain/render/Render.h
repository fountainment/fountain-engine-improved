#if !defined(_FEI_RENDER_H_)
#define _FEI_RENDER_H_

#include <GL/glew.h>

#include "base/basedef.h"
#include "base/ModuleBase.h"
#include "math/Rect.h"
#include "math/Shape.h"
#include "math/Vec2.h"
#include "math/Vec4.h"
#include "render/Camera.h"
#include "render/Color.h"
#include "render/RenderObj.h"
#include "render/Shader.h"

namespace fei {

class Render : public fei::ModuleBase
{
public:
	bool init() override;
	void destroy() override;

	void executeBeforeFrame() override;
	void executeAfterFrame() override;

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

	static void setViewport(const Rect& viewport);
	static const Rect getViewport();

	static int getMaxTextureSize();

	static void drawArray2f(const GLfloat* vertex, GLint first, GLsizei count, GLenum mode);

	static void drawLine(const Vec2& pa, const Vec2& pb);
	static void drawRect(const Vec2& size);
	static void drawQuad(const Vec2& size);
	static void drawQuadH(const Vec2& size);

	static void drawTexRect(const Vec2& size);
	static void drawTexQuad(const Vec2& size);
	static void drawTexQuadH(const Vec2& size);

	static void drawTexRect(const Vec2& size, GLfloat* texCoord);
	static void drawTexQuad(const Vec2& size, GLfloat* texCoord);
	static void drawTexQuadH(const Vec2& size, GLfloat* texCoord);

	static void drawShape(const Shape* shape);

	static void IndependentDraw(RenderObj* rObj);

	static void useColor(const Vec4* color);

	static Render* getInstance();

private:
	Render();

	Camera* currentCamera;

	ShaderProgram basicShader;
	std::stack<ShaderProgram*> shaderStack;

	std::map<int, GLuint> fileTextureMap;
	std::map<GLuint, Vec2> textureSizeMap;
	std::map<GLuint, int> textureRCMap;

	static const GLfloat stripTexCoord[8];

	static Render *instance;
};

inline void Render::drawArray2f(const GLfloat* vertex, GLint first, GLsizei count, GLenum mode)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertex);
	glDrawArrays(mode, first, count);
	glDisableClientState(GL_VERTEX_ARRAY);
}

inline void Render::drawLine(const fei::Vec2& pa, const fei::Vec2& pb)
{
	GLfloat vertex[] = {pa.x, pa.y, pb.x, pb.y};
	drawArray2f(vertex, 0, 2, GL_LINES);
}

inline void Render::drawRect(const fei::Vec2& size)
{
	GLfloat vertex[] = {-size.x, size.y, 0.0f, 0.0f, size.x, size.y, size.x, -size.y};
	drawArray2f(vertex, 0, 4, GL_TRIANGLE_STRIP);
}

inline void Render::drawQuad(const fei::Vec2& size)
{
	GLfloat w2 = size.x * 0.5f;
	GLfloat h2 = size.y * 0.5f;
	GLfloat vertex[] = {-w2, h2, -w2, -h2, w2, h2, w2, -h2};
	drawArray2f(vertex, 0, 4, GL_TRIANGLE_STRIP);
}

inline void Render::drawQuadH(const fei::Vec2& size)
{
	GLfloat w2 = size.x;
	GLfloat h2 = size.y;
	GLfloat vertex[] = {-w2, h2, -w2, -h2, w2, h2, w2, -h2};
	drawArray2f(vertex, 0, 4, GL_TRIANGLE_STRIP);
}

inline void Render::drawTexRect(const fei::Vec2& size)
{
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, stripTexCoord);
	drawRect(size);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

inline void Render::drawTexQuad(const fei::Vec2& size)
{
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, stripTexCoord);
	drawQuad(size);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

inline void Render::drawTexQuadH(const fei::Vec2& size)
{
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, stripTexCoord);
	drawQuadH(size);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

inline void Render::drawTexRect(const fei::Vec2& size, GLfloat* texCoord)
{
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
	drawRect(size);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

inline void Render::drawTexQuad(const fei::Vec2& size, GLfloat* texCoord)
{
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
	drawQuad(size);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

inline void Render::drawTexQuadH(const fei::Vec2& size, GLfloat* texCoord)
{
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
	drawQuadH(size);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

inline void Render::IndependentDraw(fei::RenderObj* rObj)
{
	glPushMatrix();
	rObj->draw();
	glPopMatrix();
}

} // namespace fei

#endif // _FEI_RENDER_H_
