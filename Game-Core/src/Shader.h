#pragma once
#include <GL\glew.h>
#include "Engine.h"
#include "Maths\mat4.h"
#include "Maths\vec2.h"
#include "Maths\vec4.h"

class Shader {
private:
	enum ShaderType {
		VertexShader,
		FragmentShader,
		GeometryShader,
	};
private:
	_int m_progID;
	std::string m_path;
	#ifdef E_DEBUG
	std::string m_ShaderShaderSource;
	std::string m_VSSourceCode;
	std::string m_FSSourceCode;
	#endif
public:
	Shader(const std::string& path);
	~Shader();
public:
	void enable();
	void disable();
private:
	void init();
public:
	void setUniform1f(const char* name, float v);
	void setUniform2f(const char* name, const vec2<float>& v);
	void setUniform4f(const char* name, const vec4<float>& v);
	void setUniformMat4f(const char* name, const mat4<float>& v);
private:
	_int getUniformLocation(const char* name);
private:
	std::string loadShader(ShaderType type);
	std::string loadShaderSourceCode(ShaderType type);
public:
	inline _int getProgId() const { return m_progID; };
public:
	static std::string GetStringFromShaderType(ShaderType type);
	static GLenum GetGLShaderType(ShaderType type);
};