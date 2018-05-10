
#include <vector>

#include "Window.h"
#include "Shader.h"
#include "Renderer.h"
#include "Maths\vec2.h"
#include "Maths\vec4.h"
#include "Maths\mat4.h"
#include "Renderable.h"
#include "Layer.h"
#include "Scene.h"
#include "Entity.h"

int main() {

	Window window(1600, 900, "Test");

	Scene scene;
	Texture t[16 * 9];
	for (int yy = 0; yy < 9.0f; yy ++) {
		for (int xx = 0; xx < 16.0f; xx++) {
			t[xx + yy * 16] = Texture("res/textures/TestImage.png");
		}
	}
	for (float yy = 0; yy <= 9.0f; yy += 0.25f) {
		for (float xx = 0; xx <= 16.0f; xx+=0.25f) {
			Entity* e = new Entity();
			e->setRenderable(vec2f(xx, yy), vec2f(1.0f), vec4f(1.0f));
			Renderable& r = e->getRenderable();
			r.setDimension(0.25f);
			r.setTexture(&t[(int)yy*16+(int)xx]);
			if (xx == 0.0f||yy==0.0f) {
				r.setColor({ 0, 0, 0, 1 });
			}
			scene.add(e);
		}
	}
	Layer& layer = scene.getWorldLayer();

	mat4f& P = layer.getProjectionMatrix();
	mat4f& V = layer.getViewMatrix();
	mat4f& M = layer.getModelMatrix();
	while (!window.shouldClose())
	{
		scene.update();
		scene.render();
		window.update();
		Timer::Update();
	}
	return 0;
}