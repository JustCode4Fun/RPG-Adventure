#include "Shader.h"

Shader::Shader(const std::string& path)
	: m_progID(-1), m_path(path)
{
	init();
}

Shader::~Shader()
{
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
	std::string m_VSSourceCode = loadShader(VertexShader);
	std::string m_FSSourceCode = loadShader(FragmentShader);
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
		Console::PrintFatal("Couldn't compile shader at path: "+m_path + " ==> " + std::string(message, log_length));
	}
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
		Console::PrintFatal("Couldn't compile the " + GetStringFromShaderType(type) + " shader from shader at path: " + m_path + " ==> "+std::string(message, logLength));
	}
	GLCall(glAttachShader(m_progID, shader));
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
