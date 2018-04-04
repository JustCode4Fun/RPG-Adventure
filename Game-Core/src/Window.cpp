#include "Window.h"
#include "Engine.h"

Window* Window::WINDOW_INSTANCE = nullptr;

Window::Window(const int width, const int height, const std::string& title)
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
	delete m_window;
}

void Window::initGLFW()
{
	Console::printError("Couldn't init GLFW!!!");
	if (!glfwInit()) {

	}
}

void Window::createGLFWWindow()
{
}

void Window::initGLEW()
{
}
