#include "Window.h"

Window::Window(const int width, const int height, const std::string& title)
	:m_width(width), m_height(height), m_title(title)
{
	initGLFW();
	createGLFWWindow();
	initGLEW();
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
	delete m_window;
}

void Window::initGLFW()
{
	if (!glfwInit()) {
		#ifdef E_DEBUG
		
		#endif
	}
}

void Window::createGLFWWindow()
{
}

void Window::initGLEW()
{
}
