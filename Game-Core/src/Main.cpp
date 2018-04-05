
#include "Window.h"

int main() {
	Window window(1600, 900, "Test");

	while (!window.shouldClose())
	{
		window.update();
	}
	return 0;
}