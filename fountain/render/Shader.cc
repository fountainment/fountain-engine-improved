#include "render/Shader.h"

#include "base/fileUtil.h"
#include "render/Render.h"

using fei::Shader;
using fei::FragmentShader;
using fei::VertexShader;
using fei::ShaderProgram;

static const GLchar *BasicVertexShader = {
	"#version 130\n"
	"in vec4 feiVertex;\n"
	"in vec2 feiTexCoord;\n"
	"out vec4 v_color;\n"
	"out vec2 v_texcoord;\n"
	"void main()\n"
	"{\n"
	"       v_color = gl_Color;\n"
	"       v_texcoord = feiTexCoord;\n"
	"       gl_Position = gl_ModelViewProjectionMatrix * feiVertex;\n"
	"}\n"
};

static const GLchar *BasicFragmentShader = {
	"#version 130\n"
	"uniform sampler2D feiTex;\n"
	"uniform bool feiUseTex;\n"
	"in vec4 v_color;\n"
	"in vec2 v_texcoord;\n"
	"void main()\n"
	"{\n"
	"       vec4 color = v_color;\n"
	"       if (feiUseTex) {\n"
	"               vec4 texColor = texture2D(feiTex, v_texcoord);\n"
	"               if (texColor.a == 0.0 || color.a == 0.0) discard;\n"
	"               color *= texColor;\n"
	"       }\n"
	"       gl_FragColor = color;\n"
	"}\n"
};

static const char *ShaderTextureSwitchUniform = "feiUseTex";
static const char *ShaderTextureIdUniform = "feiTex";

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
		loadString((char*)buffer);
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
		output += " shader compile error!\n";
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
: _id(0),
  _useTexUniformLoc(-1),
  _useTexCache(false)
{
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
		loadString((char*)vsStr, (char*)fsStr);
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

void ShaderProgram::loadBasicShader()
{
	loadString(BasicVertexShader, BasicFragmentShader);
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

void ShaderProgram::beforeLink()
{
	bindAttribLocation(0, "feiVertex");
	bindAttribLocation(2, "feiTexCoord");
}

void ShaderProgram::afterLink()
{
}

void ShaderProgram::link()
{
	beforeLink();
	glLinkProgram(_id);
	linkCheck();
	basicSetting();
	afterLink();
}

bool ShaderProgram::linkCheck()
{
	GLint linked;
	glGetProgramiv(_id, GL_LINK_STATUS, &linked);
	if (GL_FALSE == linked) {
		GLint length;
		GLchar *log;
		std::string output = "Program link error!\n";
		glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &length);
		log = new GLchar[length];
		glGetProgramInfoLog(_id, length, &length, log);
		output += std::string(log) + "\n\n";
		std::fprintf(stderr, "%s", output.c_str());
		delete [] log;
		return false;
	}
	return true;
}

void ShaderProgram::use()
{
	glUseProgram(_id);
}

void ShaderProgram::bindAttribLocation(GLuint location, const std::string& shaderVariableName)
{
	glBindAttribLocation(_id, location, shaderVariableName.c_str());
}

void ShaderProgram::bindFragDataLocation(GLuint location, const std::string& shaderVariableName)
{
	glBindFragDataLocation(_id, location, shaderVariableName.c_str());
}

void ShaderProgram::push()
{
	Render::getInstance()->pushShader(this);
}

void ShaderProgram::pop()
{
	Render::getInstance()->popShader(this);
}

GLint ShaderProgram::getUniformLocation(const std::string& varName)
{
	return glGetUniformLocation(_id, varName.c_str());
}

void ShaderProgram::setUniform(GLint varLoc, bool value)
{
	if (varLoc != -1) {
		push();
		if (value) {
			glUniform1i(varLoc, 1);
		} else {
			glUniform1i(varLoc, 0);
		}
		pop();
	}
}

void ShaderProgram::setUniform(GLint varLoc, int value)
{
	if (varLoc != -1) {
		push();
		glUniform1i(varLoc, value);
		pop();
	}
}

void ShaderProgram::setUniform(GLint varLoc, float value)
{
	if (varLoc != -1) {
		push();
		glUniform1f(varLoc, value);
		pop();
	}
}

void ShaderProgram::setUniform(GLint varLoc, const fei::Vec2& value)
{
	if (varLoc != -1) {
		push();
		glUniform2fv(varLoc, 1, &(value.x));
		pop();
	}
}

void ShaderProgram::setUniform(GLint varLoc, const fei::Vec3& value)
{
	if (varLoc != -1) {
		push();
		glUniform3fv(varLoc, 1, &(value.x));
		pop();
	}
}

void ShaderProgram::setUniform(GLint varLoc, const fei::Vec4& value)
{
	if (varLoc != -1) {
		push();
		glUniform4fv(varLoc, 1, &(value.x));
		pop();
	}
}

void ShaderProgram::setUniform(GLint varLoc, const int* value, int num)
{
	if (varLoc != -1) {
		push();
		glUniform1iv(varLoc, num, value);
		pop();
	}
}

void ShaderProgram::setUniform(GLint varLoc, const float* value, int num)
{
	if (varLoc != -1) {
		push();
		glUniform1fv(varLoc, num, value);
		pop();
	}
}

void ShaderProgram::setUniform(GLint varLoc, const fei::Vec2* value, int num)
{
	if (varLoc != -1) {
		push();
		glUniform2fv(varLoc, num, &(value->x));
		pop();
	}
}

void ShaderProgram::setUniform(GLint varLoc, const fei::Vec3* value, int num)
{
	if (varLoc != -1) {
		push();
		glUniform3fv(varLoc, num, &(value->x));
		pop();
	}
}

void ShaderProgram::setUniform(GLint varLoc, const fei::Vec4* value, int num)
{
	if (varLoc != -1) {
		push();
		glUniform4fv(varLoc, num, &(value->x));
		pop();
	}
}

void ShaderProgram::setUniform(const std::string& varName, bool value)
{
	GLint loc = getUniformLocation(varName);
	setUniform(loc, value);
}

void ShaderProgram::setUniform(const std::string& varName, int value)
{
	GLint loc = getUniformLocation(varName);
	setUniform(loc, value);
}

void ShaderProgram::setUniform(const std::string& varName, float value)
{
	GLint loc = getUniformLocation(varName);
	setUniform(loc, value);
}

void ShaderProgram::setUniform(const std::string& varName, const fei::Vec2& value)
{
	GLint loc = getUniformLocation(varName);
	setUniform(loc, value);
}

void ShaderProgram::setUniform(const std::string& varName, const fei::Vec3& value)
{
	GLint loc = getUniformLocation(varName);
	setUniform(loc, value);
}

void ShaderProgram::setUniform(const std::string& varName, const fei::Vec4& value)
{
	GLint loc = getUniformLocation(varName);
	setUniform(loc, value);
}

void ShaderProgram::setUseTex(bool useTex)
{
	if (_useTexCache != useTex) {
		setUniform(_useTexUniformLoc, useTex);
		_useTexCache = useTex;
	}
}

void ShaderProgram::basicSetting()
{
	_useTexUniformLoc = getUniformLocation(ShaderTextureSwitchUniform);
	setUniform(ShaderTextureIdUniform, 0);
}
