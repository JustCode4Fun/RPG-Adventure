#pragma once
#include "Maths\vec2.h"
#include "Maths\vec4.h"
#include "Texture.h"

#include <vector>
#include "Maths\vec2.h"

class Renderer;

class Renderable {
private:
	vec2f m_pos;
	vec2f m_dim;
	std::vector<vec2f> m_uvs;
	vec4f m_col;
	Texture* m_tex;
public:
	Renderable(const vec2f& pos, const vec2f& dim, const vec4f& col);
	~Renderable();
public:
	void submit(Renderer& r);
private:
	void setUVDefaults();
public:
	inline void setPosition(const vec2f& pos)  { m_pos = pos; };
	inline void setDimension(const vec2f& dim)  { m_dim = dim; };
	inline void setColor(const vec4f& col)  { m_col = col; };
	inline void setTexture(Texture* tex)  { m_tex = tex; };
public:
	inline void setPosition(const _float& x, const _float& y)  { m_pos.x = x; m_pos.y = y; };
	inline void setDimension(const _float& w, const _float& h)  { m_dim.x = w; m_dim.y = h; };
	inline void setColor(const _float& r, const _float& g, const _float& b, const _float& a)  { m_col.x = r; m_col.y = g; m_col.z = b; m_col.w = a;}
	inline void setTexture(const std::string& tex) { m_tex = new Texture(tex); };
public:
	inline const vec2f& getPosition() const { return m_pos; };
	inline const vec2f& getDimension() const { return m_dim; };
	inline const std::vector<vec2f>& getUVs() const { return m_uvs; };
	inline const vec4f& getColor() const { return m_col; };
	inline Texture* getTexture() const { return m_tex; };

};