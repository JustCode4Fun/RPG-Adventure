#pragma once

#include <string>
#include <glfw3.h>

class Window {
private:
	static Window* WINDOW_INSTANCE = nullptr;
private:
	const int m_width, m_height;
	const std::string m_title;

	const GLFWwindow* m_window;
public:
	Window(const int width, const int height, const std::string& title);
	~Window();
private:
	void initGLFW();
	void createGLFWWindow();
	void initGLEW();
public:
	inline const int getWidth() { return m_width; };
	inline const int getHeight() { return m_height; };
	inline const std::string& getTitle() { return m_title; };
public:
	static int getWidth() { return WINDOW_INSTANCE->m_width; };
	static int getHeight() { return WINDOW_INSTANCE->m_height; };
	static std::string& getString() { return WINDOW_INSTANCE->m_title; };
};