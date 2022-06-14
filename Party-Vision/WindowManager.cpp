#include "WindowManager.hpp"
GLFWwindow* window;
int windowWidth, windowHeight;
double scaley;
double scalex;
void windowManagerInit()
{
	int viewport[4];
	
	
	if (!glfwInit())
		throw "Could not initialize glwf";
	window = glfwCreateWindow(1920, 1080, "School Ninja", glfwGetPrimaryMonitor(), NULL);
	
	if (!window)
	{
		glfwTerminate();
		throw "Could not initialize glwf";
	}
	glfwMakeContextCurrent(window);
	glGetIntegerv(GL_VIEWPORT, viewport);
	windowWidth = viewport[2];
	windowHeight = viewport[3];
	scalex = windowWidth / 640.0;
	scaley = windowHeight / 360.0;
}
