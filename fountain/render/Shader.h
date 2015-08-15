#if !defined(_FEI_SHADER_H_)
#define _FEI_SHADER_H_

#include "base/basedef.h"
#include <GL/glew.h>

namespace fei {

class Shader
{
public:
	friend class ShaderProgram;

	void loadFromFile(std::string filename);
	void loadFromString(std::string source);

	void compile();
	bool compileCheck();
	void unload();

protected:
	Shader();
	virtual ~Shader();
	void createShader();
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
	ShaderProgram();
	~ShaderProgram();
	void attach(Shader* shader);
	void link();
	void use();

private:
	GLuint id;
};

}

#endif
