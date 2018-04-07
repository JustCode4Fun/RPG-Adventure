#include "Renderer.h"

#include <GL\glew.h>

#include "Vertex2D.h"

#define MAX_NUM_RENDERABLES 60000
#define MAX_NUM_INDICES 6 * MAX_NUM_RENDERABLES
#define MAX_NUM_VERTICES 4*MAX_NUM_RENDERABLES

Renderer::Renderer()
{
	init();
}

Renderer::~Renderer()
{
}

void Renderer::init()
{
	GLCall(glGenBuffers(1, &m_VBO));
	GLCall(glGenVertexArrays(1, &m_VAO));
	GLCall(glGenBuffers(1, &m_IBO));

	GLCall(glBindVertexArray(m_VAO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));

	GLCall(glBufferData(GL_ARRAY_BUFFER, MAX_NUM_VERTICES * sizeof(_float), NULL, GL_DYNAMIC_DRAW));

	fillIndexBuffer(m_indexBuffer);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_NUM_INDICES * sizeof(_uint), m_indexBuffer, GL_STATIC_DRAW);

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)0));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)(2*sizeof(float))));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));

	m_numIndices = 0;
}

void Renderer::fillVertexData(_float*& data, _uint& dataSize)
{
}

void Renderer::fillIndexBuffer(_uint*& indexBuffer)
{

	m_indexBuffer = new _uint[MAX_NUM_INDICES];
	int offset = 0;
	for (_uint i = 0; i < MAX_NUM_INDICES; i += 6) {
		m_indexBuffer[i + 0] = offset + 0;
		m_indexBuffer[i + 1] = offset + 1;
		m_indexBuffer[i + 2] = offset + 2;
		m_indexBuffer[i + 3] = offset + 2;
		m_indexBuffer[i + 4] = offset + 3;
		m_indexBuffer[i + 5] = offset + 0;
		offset += 4;
	}
}

void Renderer::begin()
{
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	m_vertexBuffer = (Vertex2D*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void Renderer::submit(vec2<float> pos, vec2<float> size, vec4<float> color)
{
	vec2<float> position[4] = {
		vec2<float>(pos.m_x, pos.m_y),
		vec2<float>(pos.m_x + size.m_x, pos.m_y),
		vec2<float>(pos.m_x + size.m_x, pos.m_y + size.m_y),
		vec2<float>(pos.m_x, pos.m_y + size.m_y),
	};

	m_vertexBuffer->position = position[0];
	m_vertexBuffer->color = color;
	m_vertexBuffer++;

	m_vertexBuffer->position = position[1];
	m_vertexBuffer->color = color;
	m_vertexBuffer++;

	m_vertexBuffer->position = position[2];
	m_vertexBuffer->color = color;
	m_vertexBuffer++;

	m_vertexBuffer->position = position[3];
	m_vertexBuffer->color = color;
	m_vertexBuffer++;

	m_numIndices += 6;
}

void Renderer::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderer::flush()
{

	GLCall(glBindVertexArray(m_VAO));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
	GLCall(glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, NULL));
}
