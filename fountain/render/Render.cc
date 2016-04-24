#include "render/Render.h"

#include <glad/glad.h>

#include "base/basedef.h"
#include "interface/Interface.h"
#include "math/hash.h"
#include "math/Circle.h"

using fei::Render;

const GLfloat Render::stripTexCoord_[8] = {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f};

Render* Render::instance_ = nullptr;

Render* Render::getInstance()
{
	if (!instance_) {
		instance_ = new Render();
	}
	return instance_;
}

Render::Render()
: _currentCamera(nullptr),
  _currentRenderTarget(nullptr)
{
}

bool Render::init()
{
	if (!fei::Interface::getInstance()->feiInit()) {
		return false;
	}
	std::printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	if (GL_VERSION_2_0) {
		std::printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
		_basicShader.loadBasicShader();
		_basicShader.push();
	} else {
		std::printf("Shader unsupported!\n");
	}
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	GLint maxTexSize;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
	_maxTexSize = maxTexSize;
	return true;
}

void Render::destroy()
{
	while (!_shaderStack.empty()) {
		_shaderStack.pop();
	}
	deleteUnusedTexture();
}

void Render::executeBeforeFrame()
{
	clearBuffer();
	initViewport();
	initMatrix();
	initShader();
}

void Render::executeAfterFrame()
{
	deleteUnusedTexture();
	glFlush();
}

void fei::Render::clearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void fei::Render::initViewport()
{
	auto window = fei::Interface::getInstance()->getCurrentWindow();
	if (window) {
		setViewport(fei::Rect(window->getFrameSize()));
	}
}

void fei::Render::initMatrix()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void fei::Render::initShader()
{
	auto shader = getShaderProgram();
	if (shader) {
		shader->use();
	}
}

void Render::setCurrentCamera(fei::Camera* camera)
{
	_currentCamera = camera;
}

fei::Camera* Render::getCurrentCamera()
{
	return _currentCamera;
}

void Render::setCurrentRenderTarget(fei::RenderTarget* renderTarget)
{
	_currentRenderTarget = renderTarget;
}

fei::RenderTarget* Render::getCurrentRenderTarget()
{
	return _currentRenderTarget;
}

void Render::setViewport(const fei::Rect& viewport)
{
	glViewport((GLint)viewport.getPosition().x, (GLint)viewport.getPosition().y,
		(GLsizei)viewport.getSize().x, (GLsizei)viewport.getSize().y);
	_viewport = viewport;
}

const fei::Rect Render::getViewport()
{
	return _viewport;
}

void Render::setClearColor(const fei::Vec4* color)
{
	glClearColor(color->x, color->y, color->z, color->w);
}

int Render::getMaxTextureSize()
{
	return _maxTexSize;
}

void Render::pushShader(fei::ShaderProgram* shader)
{
	if (_shaderStack.empty() || _shaderStack.top() != shader) {
		shader->use();
	}
	_shaderStack.push(shader);
}

void Render::popShader(fei::ShaderProgram* shader)
{
	if (!_shaderStack.empty() && _shaderStack.top() == shader) {
		_shaderStack.pop();
		if (_shaderStack.empty()) {
			glUseProgram(0);
		} else if (_shaderStack.top() != shader) {
			_shaderStack.top()->use();
		}
	}
}

fei::ShaderProgram* Render::getShaderProgram()
{
	if (!_shaderStack.empty()) {
		return _shaderStack.top();
	} else {
		return nullptr;
	}
}

void Render::registTexture(const std::string& filename, GLuint id)
{
	int hash = fei::bkdrHash(filename);
	_fileTextureMap[hash] = id;
}

void Render::deleteTexture(GLuint id)
{
	glDeleteTextures(1, &id);
	_textureSizeMap.erase(_textureSizeMap.find(id));
	for (auto it = _fileTextureMap.begin(); it != _fileTextureMap.end(); ++it) {
		if (it->second == id) {
			_fileTextureMap.erase(it);
			break;
		}
	}
}

int Render::queryTexture(const std::string& filename)
{
	int hash = fei::bkdrHash(filename);
	GLuint ans = 0;
	auto it = _fileTextureMap.find(hash);
	if (it != _fileTextureMap.end()) {
		ans = it->second;
	}
	return ans;
}

void Render::registTexSize(GLuint id, const fei::Vec2& size)
{
	_textureSizeMap[id] = size;
}

const fei::Vec2 Render::queryTexSize(GLuint id)
{
	return _textureSizeMap[id];
}

void Render::addRefTexture(GLuint id)
{
	if (!id) return;
	_textureRCMap[id]++;
}

void Render::releaseTexture(GLuint id)
{
	if (!id) return;
	_textureRCMap[id]--;
}

void Render::deleteUnusedTexture()
{
	for (auto it = _textureRCMap.begin(); it != _textureRCMap.end();) {
		if (it->second == 0) {
			deleteTexture(it->first);
			it = _textureRCMap.erase(it);
		} else {
			++it;
		}
	}
}

void Render::bindTexture(GLuint tex)
{
	if (!tex) return;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	auto shader = getShaderProgram();
	if (shader) {
		shader->setUseTex(true);
	}
}

void Render::disableTexture()
{
	auto shader = getShaderProgram();
	if (shader) {
		shader->setUseTex(false);
	}
}

void Render::drawShape(const fei::Shape* shape)
{
	GLenum type = GL_TRIANGLE_FAN;
	if (!shape->isSolid()) {
		type = GL_LINE_LOOP;
	}
	auto pos = shape->getPosition();
	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0.0f);
	if (fei::Shape::Type::CIRCLE == shape->getType()) {
		float r = ((fei::Circle*)shape)->getRadius();
		glScalef(r, r, r);
	} else if (fei::Shape::Type::SEGMENT == shape->getType()) {
		type = GL_LINES;
	}
	drawArray2f(shape->getDataPtr(), 0, shape->getDataSize(), type);
	glPopMatrix();
}

void Render::useColor(const fei::Vec4* color)
{
	glColor4fv(&color->x);
}

