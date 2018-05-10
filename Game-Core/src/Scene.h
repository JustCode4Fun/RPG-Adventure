#pragma once

#include "Layer.h"
#include <vector>

class Entity;

class Scene {
	friend class Entity;
private:
	Layer m_worldLayer;
	std::vector<Entity*> m_entities;
public:
	Scene();
	~Scene();
public:
	Entity* add(Entity* entity);
	void remove(Entity* entity);
public:
	void update();
	void render();
public:
	inline Layer& getWorldLayer() { return m_worldLayer; };
	inline const Layer& getWorldLayer() const { return m_worldLayer; };
	inline std::vector<Entity*>& getEntities() { return m_entities; };
};