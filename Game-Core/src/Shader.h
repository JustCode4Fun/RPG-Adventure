#pragma once
#include <GL\glew.h>
#include "Engine.h"

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
private:
	std::string loadShader(ShaderType type);
	std::string loadShaderSourceCode(ShaderType type);
public:
	inline _int getProgId() const { return m_progID; };
public:
	static std::string GetStringFromShaderType(ShaderType type);
	static GLenum GetGLShaderType(ShaderType type);
};