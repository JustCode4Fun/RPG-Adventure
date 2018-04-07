
#include "Window.h"
#include "Shader.h"

int main() {
	Window window(1600, 900, "Test");
	Shader shader("res/shaders/Test.shader");
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	_uint VAO;
	GLCall(glGenVertexArrays(1, &VAO));

	_uint VBO;
	GLCall(glBindVertexArray(VAO));
	GLCall(glGenBuffers(1, &VBO));


	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
	//GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	while (!window.shouldClose())
	{
		shader.enable();
		shader.setUniform1f("time", glfwGetTime());
		GLCall(glBindVertexArray(VAO));
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
		window.update();
	}
	return 0;
}