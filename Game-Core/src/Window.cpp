#include "Window.h"

#include "Engine.h"

#include <iostream>


Window* Window::WINDOW_INSTANCE = nullptr;

Window::Window(const _int width, const _int height, const std::string& title)
	:m_width(width), m_height(height), m_title(title)
{
	WINDOW_INSTANCE = this;
	initGLFW();
	createGLFWWindow();
	initGLEW();
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Window::initGLFW()
{
	if (!glfwInit()) {
		Console::PrintFatal("Couldn't init GLFW!!!");
		Console::Pause();
		exit(-1); // TODO: Make list of error codes
	}
	Console::Print("GLFW Version " + std::to_string(GLFW_VERSION_MAJOR) + "." + std::to_string(GLFW_VERSION_MINOR) + "." + std::to_string(GLFW_VERSION_REVISION));


}

void Window::createGLFWWindow()
{
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 9);
	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);

	if (!m_window) {
		Console::PrintFatal("Couldn't open a GLFWWindow!!!");
		Console::Pause();
		glfwTerminate();
		exit(-2); // TODO: Make list of error codes
	}

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(0.0f);
	GLCall(glEnable(GL_MULTISAMPLE));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Window::initGLEW()
{
	const GLenum err = glewInit();

	if (GLEW_OK != err) {
		Console::PrintFatal("GLEW Error: " + std::string((const char*)glewGetErrorString(err)));
	}
	std::string message((const char*)glewGetString(GLEW_VERSION));
	Console::Print("GLEW Version "+message);

}

void Window::update()
{
	glClearColor(1, 1, 0, 1);


	/* Swap front and back buffers */
	glfwSwapBuffers(m_window);
	glClear(GL_COLOR_BUFFER_BIT);
	/* Poll for and process events */
	glfwPollEvents();
}
