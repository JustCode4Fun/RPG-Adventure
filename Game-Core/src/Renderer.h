#pragma once

#include "Engine.h"
#include "Maths\vec2.h"
#include "Maths\vec4.h"
#include <vector>

struct Vertex2D;
class Renderable;
class Texture;
class Shader;


class Renderer {
static _int* TEXTURE_ID_ARRAY;
private:
	_uint m_VAO;
	_uint m_VBO;
	_uint m_IBO;
	Vertex2D* m_vertexBuffer;
	_uint* m_indexBuffer;
	_uint m_numIndices;
	std::vector<const Texture*> m_textures;
	const Shader* m_shader;
public:
	Renderer(const Shader* shader);
	~Renderer();
private:
	void init();
	void fillVertexData(_float*& data, _uint& dataSize);
	void fillIndexBuffer(_uint*& indices);
public:
	void begin();
	void submit(const vec2f& pos, const vec2f& size, const vec4f& color);
	void submit(const Renderable& r);
	void end();
	void flush();
};