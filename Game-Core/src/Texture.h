#pragma once

#include "Maths\vec2.h"
#include "Maths\vec4.h"

#include <string>

class Texture {
private:
	_uint m_tid;
	std::string m_path;
	vec2ui m_size;
	_ubyte* m_data;
public:
	Texture(const std::string& path);
	Texture(const vec2ui& dim = vec2ui(1));
	Texture(const vec2ui& dim, const vec4f& col);
public:
	void loadOpenGLTexture();
public:
	void bind(_uint target = 0) const;
	void unbind() const;
private:
	inline const std::string& getPath() const { return m_path; };


};