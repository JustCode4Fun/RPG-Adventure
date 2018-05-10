#include "Texture.h"

#include <GL\glew.h>
#include "..\ext\LodePNG\lodepng.h"

Texture::Texture(const std::string& path)
	:m_path(path)
{
	std::vector<_ubyte> dataVector;
	_uint error = lodepng::decode(dataVector, m_size.x, m_size.y, m_path);
	if (error != 0)
	{
		Console::PrintFatal("Couldn't load image at path " + path + std::string(lodepng_error_text(error)));
		Console::Pause();
	}
	m_data = new _ubyte[dataVector.size()];
	for (unsigned int i = 0; i < dataVector.size(); i++) {
		m_data[i] = dataVector[i];
	}
	loadOpenGLTexture();
}

Texture::Texture(const vec2ui& dim)
	: m_path("NO PATH: HARDCODED COLOR BUFFER!!!"), m_size(dim)
{
	m_data = new _ubyte[dim.x*dim.y * 4 * 4];
	memset(m_data, 0x00, dim.x*dim.y * 4 * 4);
}

Texture::Texture(const vec2ui& dim, const vec4f& col)
	:m_path("NO PATH: HARDCODED COLOR BUFFER!!!"), m_size(dim)
{
	m_data = new _ubyte[dim.x*dim.y*4*4];
	vec4f* vecPtr = (vec4f*)m_data;
	for (_uint i = 0; i < dim.x*dim.y; i++) {
		*vecPtr = col;
		vecPtr++;
	}
}

void Texture::loadOpenGLTexture()
{
	GLCall(glGenTextures(1, &m_tid));
	bind();
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data));
	unbind();
}

void Texture::bind(_uint target) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + target));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_tid));
}

void Texture::unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
