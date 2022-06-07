#include "WindowManager.hpp"
GLFWwindow* window;

void windowManagerInit()
{
	if (!glfwInit())
		throw "Could not initialize glwf";
	window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
	
	if (!window)
	{
		glfwTerminate();
		throw "Could not initialize glwf";
	}
	glfwMakeContextCurrent(window);
}
