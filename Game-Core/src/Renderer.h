#pragma once

#include "Engine.h"
#include "Maths\vec2.h"
#include "Maths\vec4.h"

struct Vertex2D;

class Renderer {
private:
	_uint m_VAO;
	_uint m_VBO;
	_uint m_IBO;
	Vertex2D* m_vertexBuffer;
	_uint* m_indexBuffer;
	_uint m_numIndices;
public:
	Renderer();
	~Renderer();
private:
	void init();
	void fillVertexData(_float*& data, _uint& dataSize);
	void fillIndexBuffer(_uint*& indices);
public:
	void begin();
	void submit(vec2<float> pos, vec2<float> size, vec4<float> color);
	void end();
	void flush();
};