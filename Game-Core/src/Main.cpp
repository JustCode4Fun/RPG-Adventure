
#include "Window.h"
#include "Shader.h"
#include "Renderer.h"
#include "Maths\vec2.h"
#include "Maths\vec4.h"
#include "Maths\mat4.h"

int main() {

	Window window(1600, 900, "Test");
	Shader shader("res/shaders/Test.shader");

	Renderer renderer;
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	renderer.begin();
	srand(glfwGetTime());
	for (_float yy = 0; yy < 9.0f; yy += 1.0f)
		for (_float xx = 0; xx < 16.0f; xx += 1.0f) {
			renderer.submit(vec2f(xx, yy), vec2f(1.0f), vec4f(float(rand() % 11) / 10.f, float(rand() % 11) / 10.f, float(rand() % 11) / 10.f, 1.0f));
		}
	renderer.end();

	mat4f P = mat4f::orthographic2D(0.0f, 16.0f, 0.0f, 9.0f);
	mat4f V = mat4f(1.0f);
	mat4f M = mat4f(1.0f);
	mat4f PVM = P*V*M;

	while (!window.shouldClose())
	{
		V = mat4f::translate(vec2f(sinf(glfwGetTime()), cosf(glfwGetTime())));
		PVM = P*V*M;
		shader.setUniformMat4f("PVM", PVM);
		shader.enable();
		shader.setUniform1f("time", glfwGetTime());
		renderer.flush();
		window.update();
		Timer::Update();
	}
	return 0;
}