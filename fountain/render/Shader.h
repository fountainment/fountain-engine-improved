#ifndef _FEI_SHADER_H_
#define _FEI_SHADER_H_

#include <glad/glad.h>

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

	GLuint _id;
	GLenum _shaderType;
	std::string _shaderSource;
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

	void deleteProgram();

	void loadFile(const std::string& vs, const std::string& fs);
	void loadString(const std::string& vsStr, const std::string& fsStr);
	void loadBasicShader();

	void attach(Shader* shader);
	void attach(Shader* vs, Shader* fs);

	virtual void beforeLink();
	virtual void afterLink();

	void link();
	bool linkCheck();
	void use();

	void bindAttribLocation(GLuint location, const std::string& shaderVariableName);
	void bindFragDataLocation(GLuint location, const std::string& shaderVariableName);

	void push();
	void pop();

	GLint getUniformLocation(const std::string& varName);

	void setUniform(GLint varLoc, bool value);
	void setUniform(GLint varLoc, int value);
	void setUniform(GLint varLoc, float value);
	void setUniform(GLint varLoc, const Vec2& value);
	void setUniform(GLint varLoc, const Vec3& value);
	void setUniform(GLint varLoc, const Vec4& value);

	void setUniform(GLint varLoc, const int* value, int num);
	void setUniform(GLint varLoc, const float* value, int num);
	void setUniform(GLint varLoc, const Vec2* value, int num);
	void setUniform(GLint varLoc, const Vec3* value, int num);
	void setUniform(GLint varLoc, const Vec4* value, int num);

	void setUniform(const std::string& varName, bool value);
	void setUniform(const std::string& varName, int value);
	void setUniform(const std::string& varName, float value);
	void setUniform(const std::string& varName, const Vec2& value);
	void setUniform(const std::string& varName, const Vec3& value);
	void setUniform(const std::string& varName, const Vec4& value);

	virtual void setUseTex(bool useTex);

private:
	void basicSetting();

	GLuint _id;
	GLint _useTexUniformLoc;
};

} // namespace fei

#endif // _FEI_SHADER_H_
