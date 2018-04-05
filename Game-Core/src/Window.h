#pragma once

#include <string>

#include <gl\GLEW.h>
#include <glfw3.h>
#include "Engine.h"

class Window {
private:
	static Window* WINDOW_INSTANCE;
private:
	const _int m_width, m_height;
	const std::string m_title;

	GLFWwindow* m_window;
public:
	Window(const _int width, const _int height, const std::string& title);
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
	inline const _int getWidth() { return m_width; };
	inline const _int getHeight() { return m_height; };
	inline const std::string& getTitle() { return m_title; };
public:
	static _int GetWidth() { return WINDOW_INSTANCE->m_width; };
	static _int GetHeight() { return WINDOW_INSTANCE->m_height; };
	static const std::string& GetString() { return WINDOW_INSTANCE->m_title; };
};