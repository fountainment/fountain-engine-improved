#include "Shader.h"
#include "Render.h"
#include "base/fileUtil.h"

using fei::Shader;
using fei::VertexShader;
using fei::FragmentShader;
using fei::ShaderProgram;

Shader::Shader()
: id(0), shaderType(GL_VERTEX_SHADER)
{
}

Shader::~Shader()
{
	deleteShader();
}

void Shader::deleteShader()
{
	if (id) {
		glDeleteShader(id);
		id = 0;
	}
}

void Shader::loadFile(const char* filename)
{
	auto buffer = fei::readFileBuffer(filename);
	loadString(buffer);
	delete [] buffer;
}

void Shader::loadString(const char* source)
{
	shaderSource = source;
}

void Shader::compile()
{
	if (!id) {
		id = glCreateShader(shaderType);
	}
	const GLchar* shaderStr = shaderSource.c_str();
	glShaderSource(id, 1, &shaderStr, 0);
	glCompileShader(id);
}

bool Shader::compileCheck()
{
	GLint compiled;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
	if (GL_FALSE == compiled) {
		GLint length;
		GLchar *log;
		std::string output;
		if (shaderType == GL_VERTEX_SHADER) {
			output += "Vertex";
		}
		if (shaderType == GL_FRAGMENT_SHADER) {
			output += "Fragment";
		}
		output += " shader compile failed!\n";
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		log = new GLchar[length];
		glGetShaderInfoLog(id, length, &length, log);
		output += std::string(log) + "\n\n";
		std::fprintf(stderr, "%s", output.c_str());
		delete [] log;
		return false;
	}
	return true;
}

VertexShader::VertexShader()
{
	shaderType = GL_VERTEX_SHADER;
}

FragmentShader::FragmentShader()
{
	shaderType = GL_FRAGMENT_SHADER;
}

ShaderProgram::ShaderProgram()
{
	id = 0;
}

ShaderProgram::~ShaderProgram()
{
	deleteProgram();
}

void ShaderProgram::deleteProgram()
{
	if (id) {
		glDeleteProgram(id);
		id = 0;
	}
}

void ShaderProgram::loadFile(const char* vs, const char* fs)
{
	if (!id) {
		id = glCreateProgram();
	}
	auto vsStr = fei::readFileBuffer(vs);
	auto fsStr = fei::readFileBuffer(fs);
	loadString(vsStr, fsStr);
	delete [] vsStr;
	delete [] fsStr;
}

void ShaderProgram::loadString(const char* vsStr, const char* fsStr)
{
	if (!id) {
		id = glCreateProgram();
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
	if (!shader->id) {
		shader->compile();
		if (!shader->compileCheck()) {
			return;
		}
	}
	glAttachShader(id, shader->id);
	shader->deleteShader();
}

void ShaderProgram::attach(Shader* vs, Shader* fs)
{
	attach(vs);
	attach(fs);
}

void ShaderProgram::link()
{
	glLinkProgram(id);
}

void ShaderProgram::use()
{
	glUseProgram(id);
}

void ShaderProgram::push()
{
	Render::getInstance()->pushShader(this);
}

void ShaderProgram::pop()
{
	Render::getInstance()->popShader(this);
}

void ShaderProgram::setUniform(const char* varName, float value)
{
	if (fei::Render::getInstance()->getShaderProgram() != this) {
		return;
	}
	GLint loc = glGetUniformLocation(id, varName);
	if (loc != -1) {
		glUniform1f(loc, value);
	}
}

void ShaderProgram::setUniform(const char* varName, const fei::Vec2& value)
{
	if (fei::Render::getInstance()->getShaderProgram() != this) {
		return;
	}
	GLint loc = glGetUniformLocation(id, varName);
	if (loc != -1) {
		glUniform2fv(loc, 2, &(value.x));
	}
}
