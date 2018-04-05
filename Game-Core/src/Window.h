#pragma once

#include <string>

#include <gl\GLEW.h>
#include <glfw3.h>

class Window {
private:
	static Window* WINDOW_INSTANCE;
private:
	const int m_width, m_height;
	const std::string m_title;

	GLFWwindow* m_window;
public:
	Window(const int width, const int height, const std::string& title);
	~Window();
private:
	void initGLFW();
	void createGLFWWindow();
	void initGLEW();
public:
	void update();
public:
	inline bool shouldClose() { return glfwWindowShouldClose(m_window)!=0; };
public:
	inline const int getWidth() { return m_width; };
	inline const int getHeight() { return m_height; };
	inline const std::string& getTitle() { return m_title; };
public:
	static int GetWidth() { return WINDOW_INSTANCE->m_width; };
	static int GetHeight() { return WINDOW_INSTANCE->m_height; };
	static const std::string& GetString() { return WINDOW_INSTANCE->m_title; };
};