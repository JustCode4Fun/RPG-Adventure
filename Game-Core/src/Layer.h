#pragma once

#include <vector>
#include "Maths\vec2.h"
#include "Maths\vec4.h"
#include "Maths\mat4.h"

#define MAX_NUM_RENDERABLES 0x01<<16

class Renderable;
class Renderer;
class Shader;

class Layer {
private:
	std::vector<Renderable*> m_renderQueue;
	Shader* m_shader;
	Renderer* m_renderer;
public:
	struct {
		mat4f P = mat4f(1.0f);
		mat4f V = mat4f(1.0f);
		mat4f M = mat4f(1.0f);
	} PVM;
public:
	Layer(Renderer* renderer, Shader* shader);
	Layer(const char* path, const mat4f& projMatrix);
	Layer(const char* path);
	~Layer();
public:
	void add(Renderable* r);
	void remove(Renderable* r);
public:
	void update();
	void render();
public:
	inline const std::vector<Renderable*>& getRenderQueue() const { return m_renderQueue; };
	inline std::vector<Renderable*>& getRenderQueue() { return m_renderQueue; };
	inline const mat4f& getProjectionMatrix() const { return PVM.P; };
	inline const mat4f& getViewMatrix() const { return PVM.V; };
	inline const mat4f& getModelMatrix() const { return PVM.M; };
	inline mat4f& getProjectionMatrix() { return PVM.P; };
	inline mat4f& getViewMatrix()  { return PVM.V; };
	inline mat4f& getModelMatrix() { return PVM.M; };
};