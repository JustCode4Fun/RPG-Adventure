#include "Scene.h"

#include "Layer.h"
#include "Entity.h"

Scene::Scene()
: m_worldLayer("res/shaders/test.shader")
{
}

Scene::~Scene()
{
}

Entity* Scene::add(Entity * entity)
{
	m_entities.push_back(entity);
	return entity;
}

void Scene::remove(Entity* entity)
{
}

void Scene::update()
{
	m_worldLayer.update();
}

void Scene::render()
{
	for (Entity* e : m_entities)
		e->render(m_worldLayer);
	m_worldLayer.render();
}
