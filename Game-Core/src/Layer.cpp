#include "Layer.h"


#include "Renderable.h"
#include "Renderer.h"
#include "Shader.h"

Layer::Layer(Renderer* renderer, Shader* shader)
	: m_shader(shader), m_renderer(renderer)
{
	PVM.P = mat4f::orthographic2D(0.0f, 16.0f, 0.0f, 9.0f);
	m_renderQueue.reserve(MAX_NUM_RENDERABLES);
}

Layer::Layer(const char * path, const mat4f & projMatrix)
	: m_shader(new Shader(path)), m_renderer(new Renderer(m_shader))
{
	PVM.P = projMatrix;
}

Layer::Layer(const char* path)
	: m_shader(new Shader(path)), m_renderer(new Renderer(m_shader))
{
	PVM.P = mat4f::orthographic2D(0.0f, 16.0f, 0.0f, 9.0f);
	m_renderQueue.reserve(MAX_NUM_RENDERABLES);
}

Layer::~Layer()
{
}

void Layer::add(Renderable* r)
{
	m_renderQueue.push_back(r);
}

void Layer::remove(Renderable* r)
{
	if (!r) return;
	for (_uint i = 0; i < m_renderQueue.size(); i++) {
		if (m_renderQueue[i] == r)
		{
			m_renderQueue.erase(m_renderQueue.begin() + i);
			return;
		}
	}
}

void Layer::update()
{
}

void Layer::render()
{
	m_shader->setUniformMat4f("PVM", PVM.P*PVM.V*PVM.M);

	m_shader->enable();
	m_renderer->begin();
	for (Renderable* r : m_renderQueue) {
		r->submit(*m_renderer);
	}
	m_renderer->end();
	m_renderer->flush();
	m_shader->disable();
	m_renderQueue.clear();
}
