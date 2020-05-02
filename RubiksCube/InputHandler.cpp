#include "InputHandler.h"

InputHandler * InputHandler::instance = 0;

InputHandler* InputHandler::getInstance(GLFWwindow* window, RubiksCube* rubiksCube)
{
	if (instance == 0)
	{
		instance = new InputHandler(window, rubiksCube);
	}

	return instance;
}

InputHandler::InputHandler(GLFWwindow* window, RubiksCube* rubiksCube) : m_rubiksCube(rubiksCube), m_arrowRotationSpeed(5.0), m_mixNumber(1), m_clockwise(1)
{
	glfwSetKeyCallback(window, keyCallbackStatic);
}

void InputHandler::keyCallbackStatic(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputHandler* that = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	instance->keyCallback(window, key, scancode, action, mods);
}

/**
* Handle all the key pressing callbacks
*
* @param window The window that received the event.
* @param key The keyboard key that was pressed or released.
* @param scancode The system-specific scancode of the key.
* @param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
* @param mods Bit field describing which modifier keys were held down.
*/
void InputHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	int length = rand() % 25 + 25;
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		break;

		/*---------------------- X axis -------------------*/
	case GLFW_KEY_L:
		if (action == GLFW_PRESS)
		{
			// Rotate the original left vertical face.
			m_rubiksCube->rotateFace(0, RUBIKS_CUBE_SIZE - 1, m_clockwise);
		}
		break;

	case GLFW_KEY_R:
		if (action == GLFW_PRESS) 
		{
			// Rotate the original right vertical face.
			m_rubiksCube->rotateFace(0, 0, m_clockwise);
		}
		break;

		/*---------------------- Y axis -------------------*/
	case GLFW_KEY_U:
		if (action == GLFW_PRESS) 
		{
			// Rotate the original top horizontal face.
			m_rubiksCube->rotateFace(1, RUBIKS_CUBE_SIZE - 1, m_clockwise);
		}
		break;

	case GLFW_KEY_D:
		if (action == GLFW_PRESS) 
		{
			// Rotate the original bottom horizontal face.
			m_rubiksCube->rotateFace(1, 0, m_clockwise);
		}
		break;

		/*---------------------- Z axis -------------------*/
	case GLFW_KEY_B:
		if (action == GLFW_PRESS) 
		{
			// Rotate the original back face.
			m_rubiksCube->rotateFace(2, RUBIKS_CUBE_SIZE - 1, m_clockwise);
		}
		break;

	case GLFW_KEY_F:
		if (action == GLFW_PRESS) 
		{
			// Rotate the original front face.
			m_rubiksCube->rotateFace(2, 0, m_clockwise);
		}
		break;

		/*---------------------- Rotation direction -------------------*/
	case GLFW_KEY_APOSTROPHE:
		if (action == GLFW_PRESS) 
		{
			// Flip the rotation direction.
			m_clockwise = -1 * m_clockwise;
		}
		break;

		/*---------------------- Rotation angle -------------------*/
	case GLFW_KEY_A:
		if (action == GLFW_PRESS) 
		{
			// Multiple the rotation angle by 2, max of 180.
			float angle = m_rubiksCube->getAngle();
			angle *= 2;
			if (angle > 180.0f) 
			{
				angle = 180.0f;
			}
			m_rubiksCube->setAngle(angle);
		}
		break;
	case GLFW_KEY_Z:
		if (action == GLFW_PRESS) 
		{
			// Divide the rotation angle by 2.
			float angle = m_rubiksCube->getAngle();
			angle /= 2;
			m_rubiksCube->setAngle(angle);
		}
		break;

		/*---------------------- Arrows -------------------*/
	case GLFW_KEY_UP:
		// Rotate the scene's projection 5 degress around the x axis.
		m_rubiksCube->getScene()->setProjection(rotate(m_rubiksCube->getScene()->getProjection(), m_arrowRotationSpeed, X_AXIS));
		break;

	case GLFW_KEY_DOWN:
		// Rotate the scene's projection -5 degress around the x axis.
		m_rubiksCube->getScene()->setProjection(rotate(m_rubiksCube->getScene()->getProjection(), -m_arrowRotationSpeed, X_AXIS));
		break;

	case GLFW_KEY_RIGHT:
		// Rotate the scene's projection 5 degress around the y axis.
		m_rubiksCube->getScene()->setProjection(rotate(m_rubiksCube->getScene()->getProjection(), m_arrowRotationSpeed, Y_AXIS));
		break;

	case GLFW_KEY_LEFT:
		// Rotate the scene's projection -5 degress around the y axis.
		m_rubiksCube->getScene()->setProjection(rotate(m_rubiksCube->getScene()->getProjection(), -m_arrowRotationSpeed, Y_AXIS));
		break;

		/*---------------------- 4X4 / 5X5 CUBE -------------------*/
	case GLFW_KEY_Q:
		if (action == GLFW_PRESS) 
		{
			if (RUBIKS_CUBE_SIZE == 4 || RUBIKS_CUBE_SIZE == 5) 
			{
				// Rotate the original 1 from the bottom horizontal face.
				m_rubiksCube->rotateFace(1, 1, m_clockwise);
			}
		}
		break;
	case GLFW_KEY_W:
		if (action == GLFW_PRESS) 
		{
			if (RUBIKS_CUBE_SIZE == 4 || RUBIKS_CUBE_SIZE == 5) 
			{
				// Rotate the original 2 from the bottom horizontal face.
				m_rubiksCube->rotateFace(1, 2, m_clockwise);
			}
		}
		break;
	case GLFW_KEY_E:
		if (action == GLFW_PRESS) 
		{
			if (RUBIKS_CUBE_SIZE == 4 || RUBIKS_CUBE_SIZE == 5)
			{
				// Rotate the original 1 from the right vertical face.
				m_rubiksCube->rotateFace(0, 1, m_clockwise);
			}
		}
		break;
	case GLFW_KEY_T:
		if (action == GLFW_PRESS) 
		{
			if (RUBIKS_CUBE_SIZE == 4 || RUBIKS_CUBE_SIZE == 5) 
			{
				// Rotate the original 2 from the right vertical face.
				m_rubiksCube->rotateFace(0, 2, m_clockwise);
			}
		}
		break;
	case GLFW_KEY_Y:
		if (action == GLFW_PRESS) 
		{
			if (RUBIKS_CUBE_SIZE == 4 || RUBIKS_CUBE_SIZE == 5) 
			{
				// Rotate the original 1 from the front face.
				m_rubiksCube->rotateFace(2, 1, m_clockwise);
			}
		}
		break;
	case GLFW_KEY_I:
		if (action == GLFW_PRESS)
		{
			if (RUBIKS_CUBE_SIZE == 4 || RUBIKS_CUBE_SIZE == 5)
			{
				// Rotate the original 2 from the front face.
				m_rubiksCube->rotateFace(2, 2, m_clockwise);
			}
		}
		break;

		/*---------------------- 5X5 CUBE -------------------*/
	case GLFW_KEY_O:
		if (action == GLFW_PRESS)
		{
			if (RUBIKS_CUBE_SIZE == 5)
			{
				// Rotate the original 1 from the top horizontal face.
				m_rubiksCube->rotateFace(1, 3, m_clockwise);
			}
		}
		break;
	case GLFW_KEY_P:
		if (action == GLFW_PRESS)
		{
			if (RUBIKS_CUBE_SIZE == 5) 
			{
				// Rotate the original 1 from the left vertical face.
				m_rubiksCube->rotateFace(0, 3, m_clockwise);
			}
		}
		break;
	case GLFW_KEY_G:
		if (action == GLFW_PRESS)
		{
			if (RUBIKS_CUBE_SIZE == 5)
			{
				// Rotate the original 1 from the back face.
				m_rubiksCube->rotateFace(2, 3, m_clockwise);
			}
		}
		break;

	case GLFW_KEY_M:
		//MIXER
		m_mixedfile.open("mixer.txt", ios::app);
		m_mixedfile << "==========MIXING " + to_string(RUBIKS_CUBE_SIZE) + "x" + to_string(RUBIKS_CUBE_SIZE) + " for the " + to_string(m_mixNumber) + " time ===== \n";
		for (int i = 0; i < length; i++) {
			int a = rand() % 3; int b = rand() % RUBIKS_CUBE_SIZE; int c = rand() & 1;
			m_rubiksCube->rotateFace(a, b, c);
			m_mixedfile << to_string(i + 1) + ") Rotating ";
			switch (a) {
			case 0:
				m_mixedfile << "on x axis ";
				break;
			case 1:
				m_mixedfile << "on y axis ";
				break;

			case 2:
				m_mixedfile << "on z axis ";
				break;
			}

			switch (b)
			{
			case RUBIKS_CUBE_SIZE - 1:
				m_mixedfile << "the " + to_string(RUBIKS_CUBE_SIZE - 1) + " face ";
				break;
			case RUBIKS_CUBE_SIZE - 2:
				m_mixedfile << "the " + to_string(RUBIKS_CUBE_SIZE - 2) + " face ";
				break;
			case RUBIKS_CUBE_SIZE - 3:
				m_mixedfile << "the " + to_string(RUBIKS_CUBE_SIZE - 3) + " face ";
				break;
			case RUBIKS_CUBE_SIZE - 4:
				m_mixedfile << "the " + to_string(RUBIKS_CUBE_SIZE - 4) + " face ";
				break;
			case RUBIKS_CUBE_SIZE - 5:
				m_mixedfile << "the " + to_string(RUBIKS_CUBE_SIZE - 5) + " face ";
				break;
			}

			switch (c) 
			{
			case 0:
				m_mixedfile << " m_clockwise .\n";
				break;
			case 1:
				m_mixedfile << "counterclockwise .\n";
				break;
			}
			Sleep(1);
		}
		m_mixedfile << "=========Finished=======\n\n";

		m_mixNumber++;
		break;

	default:
		break;
	}
}

InputHandler::~InputHandler()
{
	m_mixedfile.close();
}