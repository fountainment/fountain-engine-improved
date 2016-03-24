#include "render/Shader.h"

#include "base/fileUtil.h"
#include "render/Render.h"

using fei::Shader;
using fei::FragmentShader;
using fei::VertexShader;
using fei::ShaderProgram;

Shader::Shader()
: _id(0),
  _shaderType(GL_VERTEX_SHADER)
{
}

Shader::~Shader()
{
	deleteShader();
}

void Shader::deleteShader()
{
	if (_id) {
		glDeleteShader(_id);
		_id = 0;
	}
}

void Shader::loadFile(const std::string& filename)
{
	auto buffer = fei::readFileBuffer(filename);
	if (buffer) {
		loadString(buffer);
		delete [] buffer;
	}
}

void Shader::loadString(const std::string& source)
{
	_shaderSource = source;
}

void Shader::compile()
{
	if (!_id) {
		_id = glCreateShader(_shaderType);
	}
	const GLchar* shaderStr = _shaderSource.c_str();
	glShaderSource(_id, 1, &shaderStr, 0);
	glCompileShader(_id);
}

bool Shader::compileCheck()
{
	GLint compiled;
	glGetShaderiv(_id, GL_COMPILE_STATUS, &compiled);
	if (GL_FALSE == compiled) {
		GLint length;
		GLchar *log;
		std::string output;
		if (_shaderType == GL_VERTEX_SHADER) {
			output += "Vertex";
		} else {
			if (_shaderType == GL_FRAGMENT_SHADER) {
				output += "Fragment";
			}
		}
		output += " shader compile failed!\n";
		glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &length);
		log = new GLchar[length];
		glGetShaderInfoLog(_id, length, &length, log);
		output += std::string(log) + "\n\n";
		std::fprintf(stderr, "%s", output.c_str());
		delete [] log;
		return false;
	}
	return true;
}

VertexShader::VertexShader()
{
	_shaderType = GL_VERTEX_SHADER;
}

FragmentShader::FragmentShader()
{
	_shaderType = GL_FRAGMENT_SHADER;
}

ShaderProgram::ShaderProgram()
{
	_id = 0;
}

ShaderProgram::~ShaderProgram()
{
	deleteProgram();
}

void ShaderProgram::deleteProgram()
{
	if (_id) {
		glDeleteProgram(_id);
		_id = 0;
	}
}

void ShaderProgram::loadFile(const std::string& vs, const std::string& fs)
{
	if (!_id) {
		_id = glCreateProgram();
	}
	auto vsStr = fei::readFileBuffer(vs);
	auto fsStr = fei::readFileBuffer(fs);
	if (vsStr && fsStr) {
		loadString(vsStr, fsStr);
	} else {
		std::fprintf(stderr, "ShaderProgram: loadFile failed!\n");
	}
	if (vsStr) {
		delete [] vsStr;
	}
	if (fsStr) {
		delete [] fsStr;
	}
}

void ShaderProgram::loadString(const std::string& vsStr, const std::string& fsStr)
{
	if (!_id) {
		_id = glCreateProgram();
	}
	VertexShader vert;
	FragmentShader frag;
	vert.loadString(vsStr);
	frag.loadString(fsStr);
	vert.compile();
	vert.compileCheck();
	frag.compile();
	frag.compileCheck();
	attach(&vert, &frag);
	link();
}

void ShaderProgram::attach(Shader* shader)
{
	if (!shader->_id) {
		shader->compile();
		if (!shader->compileCheck()) {
			return;
		}
	}
	glAttachShader(_id, shader->_id);
	shader->deleteShader();
}

void ShaderProgram::attach(Shader* vs, Shader* fs)
{
	attach(vs);
	attach(fs);
}

void ShaderProgram::link()
{
	glLinkProgram(_id);
}

void ShaderProgram::use()
{
	glUseProgram(_id);
}

void ShaderProgram::push()
{
	Render::getInstance()->pushShader(this);
}

void ShaderProgram::pop()
{
	Render::getInstance()->popShader(this);
}

void ShaderProgram::setUniform(const std::string& varName, int value)
{
	push();
	GLint loc = glGetUniformLocation(_id, varName.c_str());
	if (loc != -1) {
		glUniform1i(loc, value);
	}
	pop();
}

void ShaderProgram::setUniform(const std::string& varName, float value)
{
	push();
	GLint loc = glGetUniformLocation(_id, varName.c_str());
	if (loc != -1) {
		glUniform1f(loc, value);
	}
	pop();
}

void ShaderProgram::setUniform(const std::string& varName, const fei::Vec2& value)
{
	push();
	GLint loc = glGetUniformLocation(_id, varName.c_str());
	if (loc != -1) {
		glUniform2fv(loc, 1, &(value.x));
	}
	pop();
}

void ShaderProgram::setUniform(const std::string& varName, const fei::Vec3& value)
{
	push();
	GLint loc = glGetUniformLocation(_id, varName.c_str());
	if (loc != -1) {
		glUniform3fv(loc, 1, &(value.x));
	}
	pop();
}

void ShaderProgram::setUniform(const std::string& varName, const fei::Vec4& value)
{
	push();
	GLint loc = glGetUniformLocation(_id, varName.c_str());
	if (loc != -1) {
		glUniform4fv(loc, 1, &(value.x));
	}
	pop();
}
