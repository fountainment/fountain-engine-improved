#if !defined(_FEI_SHADER_H_)
#define _FEI_SHADER_H_

#include "base/basedef.h"
#include "math/Vec2.h"
#include <GL/glew.h>

namespace fei {

class Shader
{
public:
	friend class ShaderProgram;

	void loadFile(const char* filename);
	void loadString(const char* source);

	void compile();
	bool compileCheck();
	void unload();

protected:
	Shader();
	virtual ~Shader();
	void deleteShader();

	GLuint id;
	GLenum shaderType;
	std::string shaderSource;
};

class VertexShader : public Shader
{
public:
	VertexShader();
};

class FragmentShader : public Shader
{
public:
	FragmentShader();
};

class ShaderProgram
{
public:
	friend class Render;

	ShaderProgram();
	~ShaderProgram();

	void deleteProgram();

	void loadFile(const char* vs, const char* fs);
	void loadString(const char* vsStr, const char* fsStr);

	void attach(Shader* shader);
	void attach(Shader* vs, Shader* fs);

	void link();
	void use();

	void push();
	void pop();

	void setUniform(const char* varName, float value);
	void setUniform(const char* varName, const Vec2& value);

private:
	GLuint id;
};

}

#endif
