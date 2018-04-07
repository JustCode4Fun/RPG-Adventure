
#include "Window.h"
#include "Shader.h"
#include "Renderer.h"
#include "Maths\vec2.h"
#include "Maths\vec4.h"

int main() {
	Window window(1600, 900, "Test");
	Shader shader("res/shaders/Test.shader");
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	/*_uint VAO;
	GLCall(glGenVertexArrays(1, &VAO));

	_uint VBO;
	GLCall(glBindVertexArray(VAO));
	GLCall(glGenBuffers(1, &VBO));


	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	*/

	Renderer renderer;
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	renderer.begin();
	for(_float yy = 0; yy < 9.0f; yy+=1.0f)
		for(_float xx = 0; xx < 16.0f; xx+=1.0f)
			renderer.submit(vec2<float>(xx, yy), vec2<float>(1.0f), vec4<float>(float(rand()%11)/10.f, float(rand() % 11) / 10.f, float(rand() % 11) / 10.f, 1.0f));
	renderer.end();

	while (!window.shouldClose())
	{
		shader.enable();
		shader.setUniformMat4f("PVM", mat4<float>::orthographic2D(0.0f, 16.0f, 0.0f, 9.0f));
		shader.setUniform1f("time", glfwGetTime());
		/*GLCall(glBindVertexArray(VAO));
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));*/
		renderer.flush();
		window.update();
	}
	return 0;
}