#pragma once

#include "Maths\vec2.h"
#include "Maths\vec4.h"
#include "Maths\mat4.h"

class Renderable;
class Scene;
class Layer;

class Entity {
private:
	Renderable* m_renderable;
private:
	Scene* m_scene;
	Layer* m_layer;
public:
	Entity();
	Entity(Scene* scene);
	Entity(Renderable* renderable);
	~Entity();
public:
	void add(Scene* scene);
public:
	void update();
	void render(Layer& layer);
public:
	void setRenderable(Renderable* renderable);
	void setRenderable(const vec2f& pos, const vec2f& dim, const vec4f& col);
public:
	inline const Renderable& getRenderable() const { return *m_renderable; };
	inline Renderable& getRenderable() { return *m_renderable; };
};