#pragma once
#include <RubiksCube.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;
using namespace glm;

class InputHandler
{
public:
	/* Static access method. */
	static InputHandler* getInstance(GLFWwindow* window, RubiksCube* rubiksCube);

	static void keyCallbackStatic(GLFWwindow* window, int key, int scancode, int action, int mods);
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	~InputHandler();

private:
	/* Here will be the instance stored. */
	static InputHandler* instance;

	InputHandler(GLFWwindow* window, RubiksCube* rubiksCube);

	RubiksCube * m_rubiksCube;
	int m_clockwise;
	float m_arrowRotationSpeed;
	int m_mixNumber;
	ofstream m_mixedfile;
};

