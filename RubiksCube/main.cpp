
#include "display.h"
#include <Windows.h>
#include <RubiksCube.h>
#include <InputHandler.h>

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 800;

int main(int argc, char** argv)
{
	// Initialise the window with a rubiksCube.
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	RubiksCube* rubiksCube = new RubiksCube(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	InputHandler* inputHandler = InputHandler::getInstance(display.m_window, rubiksCube);

	while (!glfwWindowShouldClose(display.m_window))
	{
		Sleep(3);

		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);
		
		rubiksCube->draw();

		display.SwapBuffers();

		glfwPollEvents();
	}
	return 0;
}