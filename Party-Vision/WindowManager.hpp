#pragma once
#include <GLFW/glfw3.h>

/// <summary>
/// initialize glfw window
/// </summary>
void windowManagerInit();

extern GLFWwindow* window;
extern int windowWidth, windowHeight;
extern double scaley;
extern double scalex;
