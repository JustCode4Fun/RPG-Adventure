#include "Renderable.h"



#include "Renderer.h"

Renderable::Renderable(const vec2f& pos, const vec2f& dim, const vec4f& col)
	:m_pos(pos), m_dim(dim), m_col(col), m_tex(nullptr)
{
	setUVDefaults();
}

Renderable::~Renderable()
{
}

void Renderable::submit(Renderer& r)
{
	r.submit(*this);
}

void Renderable::setUVDefaults()
{
	m_uvs.reserve(4);
	m_uvs.push_back(vec2f(0, 0));
	m_uvs.push_back(vec2f(1, 0));
	m_uvs.push_back(vec2f(1, 1));
	m_uvs.push_back(vec2f(0, 1));
}
