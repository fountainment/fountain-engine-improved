#include "Shader.h"

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

void Shader::createShader()
{
	if (!id) {
		id = glCreateShader(shaderType);
	}
}

void Shader::deleteShader()
{
	if (id) {
		glDeleteShader(id);
		id = 0;
	}
}

void Shader::compile()
{
	if (!id) createShader();
	const GLchar* shaderStr = shaderSource.c_str();
	glShaderSource(id, 1, &shaderStr, 0);
	glCompileShader(id);
	compileCheck();
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
	id = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	if (id) {
		glDeleteProgram(id);
	}
}

void ShaderProgram::attach(Shader* shader)
{
	if (!shader->id) shader->compile();
	glAttachShader(id, shader->id);
	shader->deleteShader();
}

void ShaderProgram::link()
{
	glLinkProgram(id);
}

void ShaderProgram::use()
{
	glUseProgram(id);
}
