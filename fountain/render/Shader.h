#if !defined(_FEI_SHADER_H_)
#define _FEI_SHADER_H_

#include <GL/glew.h>

#include "base/basedef.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"

namespace fei {

class Shader
{
public:
	friend class ShaderProgram;

	void loadFile(const std::string& filename);
	void loadString(const std::string& source);

	void compile();
	bool compileCheck();

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

	void loadFile(const std::string& vs, const std::string& fs);
	void loadString(const std::string& vsStr, const std::string& fsStr);

	void attach(Shader* shader);
	void attach(Shader* vs, Shader* fs);

	void link();
	void use();

	void push();
	void pop();

	void setUniform(const std::string& varName, int value);
	void setUniform(const std::string& varName, float value);
	void setUniform(const std::string& varName, const Vec2& value);
	void setUniform(const std::string& varName, const Vec3& value);
	void setUniform(const std::string& varName, const Vec4& value);

private:
	GLuint id;
};

} // namespace fei

#endif // _FEI_SHADER_H_
