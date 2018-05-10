#include "Entity.h"

#include "Scene.h"
#include "Layer.h"
#include "Renderable.h"
#include <vector>

Entity::Entity()
	: m_renderable(nullptr), m_scene(nullptr), m_layer(nullptr) // TODO: Have error-renderable for safety;
{
}

Entity::Entity(Scene* scene)
	: m_renderable(nullptr), m_scene(scene), m_layer(&scene->getWorldLayer()) // TODO: Have error-renderable for safety;
{
}

Entity::Entity(Renderable* renderable)
	: m_renderable(renderable), m_scene(nullptr), m_layer(nullptr)
{
	m_layer->add(m_renderable);
}

Entity::~Entity()
{

}

void Entity::add(Scene* scene)
{
	scene->add(this);
}

void Entity::update()
{
}

void Entity::render(Layer& layer)
{
	layer.add(m_renderable);
}

void Entity::setRenderable(Renderable* renderable)
{
	m_renderable = renderable;
}

void Entity::setRenderable(const vec2f & pos, const vec2f & dim, const vec4f & col)
{
	setRenderable(new Renderable(pos, dim, col));
}
