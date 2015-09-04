#include "Render.h"
#include "interface/Interface.h"
#include "base/basedef.h"
#include "math/hash.h"
#include <GL/glew.h>

using fei::Render;

static const GLchar *basicVertexShader = {
	"void main()"
	"{"
	"	gl_TexCoord[0] = gl_MultiTexCoord0;"
	"	gl_FrontColor = gl_Color;"
	"	gl_Position = ftransform();"
	"}"
};

static const GLchar *basicFragmentShader = {
	"uniform sampler2D feiTex;"
	"uniform float feiUseTex;"
	"void main() {"
	"	vec4 color = gl_Color;"
	"	if (feiUseTex == 1.0) {"
	"		vec4 texColor = texture2D(feiTex, gl_TexCoord[0].st);"
	"		if (texColor.a == 0.0 || color.a == 0.0) discard;"
	"		color *= texColor;"
	"	}"
	"	gl_FragColor = color;"
	"}"
};

Render* Render::instance = nullptr;

Render* Render::getInstance()
{
	if (!instance) {
		instance = new Render();
	}
	return instance; 
}

Render::Render()
{
}

bool Render::init()
{
	if (!fei::Interface::getInstance()->init()) {
		return false;
	}
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return false;
	} else {
		std::printf("GLEW Version: %s\n", glewGetString(GLEW_VERSION));
		std::printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
		if (GLEW_VERSION_2_0) {
			std::printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
			basicShader.loadString(basicVertexShader, basicFragmentShader);
			basicShader.push();
		} else {
			std::printf("Shader unsupported!\n");
		}
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
	}
	return true;
}

void Render::destroy()
{
	while (!shaderStack.empty()) {
		shaderStack.pop();
	}
	deleteUnusedTexture();
}

void Render::executeBeforeFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	auto shader = getShaderProgram();
	if (shader) {
		shader->use();
	}
}

void Render::executeAfterFrame()
{
	deleteUnusedTexture();
}

void Render::setViewport(const fei::Rect& viewport)
{
	glViewport((GLint)viewport.getPosition().x, (GLint)viewport.getPosition().y,
		(GLsizei)viewport.getSize().x, (GLsizei)viewport.getSize().y);
}

const fei::Rect Render::getViewport()
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	return fei::Rect((float)viewport[0], (float)viewport[1], (float)viewport[2], (float)viewport[3]);
}

void Render::pushShader(fei::ShaderProgram* shader)
{
	if (shaderStack.empty() || shaderStack.top() != shader) {
		shaderStack.push(shader);
		shader->use();
	}
}

void Render::popShader(fei::ShaderProgram* shader)
{
	if (!shaderStack.empty() && shaderStack.top() == shader) {
		shaderStack.pop();
		if (shaderStack.empty()) {
			glUseProgram(0);
		} else {
			shaderStack.top()->use();
		}
	}
}

fei::ShaderProgram* Render::getShaderProgram()
{
	if (!shaderStack.empty()) {
		return shaderStack.top();
	} else {
		return nullptr;
	}
}

void Render::registTexture(const char* filename, GLuint id)
{
	int hash = fei::bkdrHash(filename);
	fileTextureMap[hash] = id;
}

void Render::deleteTexture(GLuint id)
{
	glDeleteTextures(1, &id);
	textureSizeMap.erase(textureSizeMap.find(id));
	for (auto it = fileTextureMap.begin(); it != fileTextureMap.end(); ++it) {
		if (it->second == id) {
			fileTextureMap.erase(it);
			break;
		}
	}
}

int Render::queryTexture(const char* filename)
{
	int hash = fei::bkdrHash(filename);
	GLuint ans = 0;
	auto it = fileTextureMap.find(hash);
	if (it != fileTextureMap.end()) {
		ans = it->second;
	}
	return ans;
}

void Render::registTexSize(GLuint id, const fei::Vec2& size)
{
	textureSizeMap[id] = size;
}

const fei::Vec2 Render::queryTexSize(GLuint id)
{
	return textureSizeMap[id];
}

void Render::addRefTexture(GLuint id)
{
	if (!id) return;
	textureRCMap[id]++;
}

void Render::releaseTexture(GLuint id)
{
	if (!id) return;
	textureRCMap[id]--;
}

void Render::deleteUnusedTexture()
{
	for (auto it = textureRCMap.begin(); it != textureRCMap.end();) {
		if (it->second == 0) {
			deleteTexture(it->first);
			it = textureRCMap.erase(it);
		} else {
			++it;
		}
	}
}

void Render::bindTexture(GLuint tex)
{
	glBindTexture(GL_TEXTURE_2D, tex);
	auto shader = getShaderProgram();
	if (shader) {
		shader->setUniform("feiUseTex", 1.0f);
		shader->setUniform("feiTex", (float)tex);
	}
}

void Render::disableTexture()
{
	auto shader = getShaderProgram();
	if (shader) {
		shader->setUniform("feiUseTex", 0.0f);
	}
}

void Render::drawTexQuad(const fei::Vec2& size, GLfloat* texCoord)
{
	GLfloat w2 = size.x / 2.0f;
	GLfloat h2 = size.y / 2.0f;
	GLfloat vertex[] = {-w2, h2, -w2, -h2, w2, h2, w2, -h2};
	GLfloat defaultTexCoord[] = {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f};
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertex);
	if (texCoord) {
		glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
	} else {
		glTexCoordPointer(2, GL_FLOAT, 0, defaultTexCoord);
	}
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Render::drawShape(const fei::Shape* shape)
{
	GLenum type = GL_TRIANGLE_FAN;
	if (!shape->isSolid()) {
		type = GL_LINE_LOOP;
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, shape->getDataPtr());
	glDrawArrays(type, 0, shape->getDataSize());
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Render::useColor(const fei::Vec4* color)
{
	glColor4fv(&color->x);
}