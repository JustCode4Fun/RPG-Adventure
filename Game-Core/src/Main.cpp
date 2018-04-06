
#include "Window.h"
#include "Shader.h"

int main() {
	Window window(1600, 900, "Test");
	Shader shader("res/shaders/Test.shader");
	Console::Pause();

	while (!window.shouldClose())
	{
		window.update();
	}
	return 0;
}