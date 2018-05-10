#include "Renderer.h"

#include <GL\glew.h>

#include "Vertex2D.h"
#include "Renderable.h"
#include "Texture.h"
#include "Shader.h"

#define MAX_NUM_RENDERABLES 60000
#define MAX_NUM_INDICES 6 * MAX_NUM_RENDERABLES
#define MAX_NUM_VERTICES 4*MAX_NUM_RENDERABLES

static _int* fillTextureArray(_uint size) {
	_int* arr = new _int[size];
	for (_uint i = 0; i < size; i++) {
		arr[i] = i;
	}
	return arr;
}
_int* Renderer::TEXTURE_ID_ARRAY = fillTextureArray(32);// TODO: Change 32 to #define MAX_TEXTURES

Renderer::Renderer(const Shader* shader)
	:m_shader(shader)
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

	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_NUM_INDICES * sizeof(_uint), m_indexBuffer, GL_STATIC_DRAW));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, position)));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, uv)));
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, color)));
	GLCall(glEnableVertexAttribArray(3));
	GLCall(glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, m_tid)));

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
	GLCall(glBindVertexArray(m_VAO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
	GLCall(m_vertexBuffer = (Vertex2D*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
}

void Renderer::submit(const vec2f& pos, const vec2f& size, const vec4f& color)
{
	/*vec2f position[4] = {
		vec2f(pos.x, pos.y),
		vec2f(pos.x + size.x, pos.y),
		vec2f(pos.x + size.x, pos.y + size.y),
		vec2f(pos.x, pos.y + size.y),
	};

	const std::vector<vec2f>& uvs = ;

	m_vertexBuffer->position = position[0];
	m_
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

	m_numIndices += 6;*/
}

void Renderer::submit(const Renderable& r)
{
	const vec2f& pos = r.getPosition();
	const vec2f& size = r.getDimension();
	vec2f position[4] = {
		vec2f(pos.x, pos.y),
		vec2f(pos.x + size.x, pos.y),
		vec2f(pos.x + size.x, pos.y + size.y),
		vec2f(pos.x, pos.y + size.y),
	};
	const std::vector<vec2f>& uvs = r.getUVs();
	const vec4f& color = r.getColor();
	const Texture* texture = r.getTexture();

	float m_tid = 0.0f;
	bool found = false;
	for (_uint i = 0; i < m_textures.size(); i++) {
		if (m_textures[i] == texture) {
			m_tid = (float)(i+1);
			found = true;
			break;
		}
	}
	if (!found) {
		if (m_textures.size() == 32) {// TODO: Change 32 to #define MAX_TEXTURES
			end();
			flush();
			begin();
		}
		m_textures.push_back(texture);
		m_tid = (float)m_textures.size();
	}

	m_vertexBuffer->position = position[0];
	m_vertexBuffer->uv = uvs[0];
	m_vertexBuffer->color = color;
	m_vertexBuffer->m_tid = m_tid;
	m_vertexBuffer++;

	m_vertexBuffer->position = position[1];
	m_vertexBuffer->uv = uvs[1];
	m_vertexBuffer->color = color;
	m_vertexBuffer->m_tid = m_tid;
	m_vertexBuffer++;

	m_vertexBuffer->position = position[2];
	m_vertexBuffer->uv = uvs[2];
	m_vertexBuffer->color = color;
	m_vertexBuffer->m_tid = m_tid;
	m_vertexBuffer++;

	m_vertexBuffer->position = position[3];
	m_vertexBuffer->uv = uvs[3];
	m_vertexBuffer->color = color;
	m_vertexBuffer->m_tid = m_tid;
	m_vertexBuffer++;

	m_numIndices += 6;
}

void Renderer::end()
{
	GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

void Renderer::flush()
{
	GLCall(glBindVertexArray(m_VAO));
	for (_uint i = 0; i < m_textures.size(); i++) {
		m_textures[i]->bind(i);
	}
	m_shader->setUniform1iv("tex", m_textures.size(), TEXTURE_ID_ARRAY);
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
	GLCall(glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, NULL));
	m_numIndices = 0;
	m_textures.clear();
}
