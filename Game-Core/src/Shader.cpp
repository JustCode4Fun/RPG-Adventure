#include "Shader.h"

Shader::Shader(const std::string& path)
	: m_progID(-1), m_path(path)
{
	init();
}

Shader::~Shader()
{
	glDeleteProgram(m_progID);
}

void Shader::enable()
{
	glUseProgram(m_progID);
}

void Shader::disable()
{
	glUseProgram(0);
}

void Shader::init()
{
	m_ShaderShaderSource = loadFileToString(m_path);

	GLCall(m_progID = glCreateProgram());

	#ifdef E_DEBUG
	m_VSSourceCode = loadShader(VertexShader);
	m_FSSourceCode = loadShader(FragmentShader);
	#else
	loadShader(VertexShader);
	loadShader(FragmentShader);
	#endif


	GLCall(glLinkProgram(m_progID));

	GLint status;
	GLCall(glGetProgramiv(m_progID, GL_LINK_STATUS, &status));
	if (status != GL_TRUE)
	{
		_int log_length = 0;
		char message[512];
		GLCall(glGetProgramInfoLog(m_progID, 512, &log_length, message));
		Console::PrintFatal("Couldn't compile shader at path: " + m_path + " ==> " + std::string(message, log_length));
	}
}

void Shader::setUniform1f(const char * name, float v)const
{
	glProgramUniform1f(m_progID, getUniformLocation(name), v);
}

void Shader::setUniform2f(const char * name, const vec2<float>& v)const
{
	glProgramUniform1fv(m_progID, getUniformLocation(name), 1, &v.x);
}

void Shader::setUniform4f(const char * name, const vec4<float>& v)const
{
	glProgramUniform2fv(m_progID, getUniformLocation(name), 1, & v.x);
}

void Shader::setUniformMat4f(const char * name, const mat4<float>& v)const
{
	glProgramUniformMatrix4fv(m_progID, getUniformLocation(name), 1, GL_FALSE, v.m_elements);
}

void Shader::setUniform1iv(const char* name, _uint count, _int* data)const
{
	glProgramUniform1iv(m_progID, getUniformLocation(name), count, data);
}

_int Shader::getUniformLocation(const char * name)const
{
	return glGetUniformLocation(m_progID, name);
}

std::string Shader::GetStringFromShaderType(ShaderType type)
{
	switch (type)
	{
	case Shader::VertexShader:
		return "vertex";
	case Shader::FragmentShader:
		return "fragment";
	case Shader::GeometryShader:
		return "geometry";
	default:
		Console::PrintWarning("ShaderType not recognized! Default \"\" string was returned.");
		return "";
	}
}

GLenum Shader::GetGLShaderType(ShaderType type)
{
	switch (type)
	{
	case Shader::VertexShader:
		return GL_VERTEX_SHADER;
	case Shader::FragmentShader:
		return GL_FRAGMENT_SHADER;
	case Shader::GeometryShader:
		return GL_GEOMETRY_SHADER;
	default:
		Console::PrintWarning("ShaderType not recognized! Default \"\" string was returned.");
		return GLenum();
	}
}

std::string Shader::loadShader(ShaderType type)
{
	std::string src = loadShaderSourceCode(type);
	const char* src_ptr = src.c_str();
	GLCall(_uint shader = glCreateShader(GetGLShaderType(type)));
	GLCall(glShaderSource(shader, 1, &src_ptr, NULL));
	GLCall(glCompileShader(shader));
	_int success;
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
	if (!success) {
		_int logLength;
		char message[512];
		GLCall(glGetShaderInfoLog(shader, 512, &logLength, message));
		Console::PrintFatal("Couldn't compile the " + GetStringFromShaderType(type) + " shader from shader at path: " + m_path + " ==> " + std::string(message, logLength));
	}
	GLCall(glAttachShader(m_progID, shader));
	GLCall(glDeleteShader(shader));
	return src;
}

std::string Shader::loadShaderSourceCode(ShaderType type)
{
	std::string tag("#shader ");
	tag += Shader::GetStringFromShaderType(type);
	size_t tagOffset = m_ShaderShaderSource.find(tag);
	if (tagOffset == std::string::npos) {
		Console::PrintError("Couldn't find " + GetStringFromShaderType(type) + " section in shader at path: " + m_path);
		return "";
	}
	size_t start = tagOffset + tag.size();
	size_t end = m_ShaderShaderSource.find("#shader", start);
	return m_ShaderShaderSource.substr(start, end - tag.size());
}
