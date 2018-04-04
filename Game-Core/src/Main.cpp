#include <gl\GLEW.h>
#include <glfw3.h>
#include <math.h>
#include <iostream>
#include "Engine.h"

int main() {

	Console::printDMessage("There is an interesting message for you: Welcome!");
	Console::printDWarning("Just wanted to warn you!!!");
	Console::printDError("Couldn't init GLFW!\nSomething went terribly wrong!!!");
	system("pause");
	return 0;
	GLFWwindow* window;

	/* Initialize the library */
	
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	const GLenum err = glewInit();

	if (GLEW_OK != err)
	{
		std::cout << "GLEW Error: " << glewGetErrorString(err) << std::endl;
	}


	/* Loop until the user closes the window */

	float alpha;
	while (!glfwWindowShouldClose(window))
	{
		alpha = cosf(glfwGetTime())*0.5f+0.5f;
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1, 1, 0, 1);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_TRIANGLES);
		glColor4f(1.0f, 0.0f, 1.0f, alpha);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(-0.5f, -0.5f);
		glEnd();
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}