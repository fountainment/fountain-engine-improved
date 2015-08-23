#include "Render.h"
#include "interface/Interface.h"
#include "base/basedef.h"
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
	"		color *= texture2D(feiTex, gl_TexCoord[0].st);"
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
	if (_isLoad) return true;
	_isLoad = true;
	if (!fei::Interface::getInstance()->init()) {
		_isLoad = false;
		return false;
	}
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		_isLoad = false;
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
		glAlphaFunc(GL_GREATER, 0.0f);
	}
	return _isLoad;
}

void Render::destroy()
{
	while (!shaderStack.empty()) {
		shaderStack.pop();
	}
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

void Render::setViewport(const fei::Rect& viewport)
{
	glViewport((GLint)viewport.getPosition().x, (GLint)viewport.getPosition().y,
		(GLsizei)viewport.getSize().x, (GLsizei)viewport.getSize().y);
}

const fei::Rect Render::getViewport()
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	return fei::Rect(viewport[0], viewport[1], viewport[2], viewport[3]);
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

void Render::bindTexture(GLuint tex)
{
	glBindTexture(GL_TEXTURE_2D, tex);
	auto shader = getShaderProgram();
	if (shader) {
		shader->setUniform("feiUseTex", 1.0f);
		shader->setUniform("feiTex", (float)tex);
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
