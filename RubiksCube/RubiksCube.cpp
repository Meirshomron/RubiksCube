#include "RubiksCube.h"

RubiksCube::RubiksCube(int width, int height) : m_angle(90.0f)
{
	// Initialise scene shader.
	m_shader = new Shader("./res/shaders/basicShader");

	// Initialise scene MVP.
	m_scene = new SceneData(vec3(0, 0, -15), Z_AXIS, Y_AXIS);
	m_scene->setPerspectiveProjection(60.0f, (float)width / (float)height, 0.1f, 100.0f);
	m_scene->setProjection(mat4((m_scene->getProjection()))*lookAt(vec3(m_scene->getPos()), vec3(m_scene->getPos() + m_scene->getForward()), vec3(m_scene->getUp())));
	m_scene->muliplyMVP();

	// Create a single cube and render it every frame RUBIKS_CUBE_SIZE^3 times.
	m_cube = new Cube(0, 0, 0, CUBE_SIZE);

	// Initialise the rotational matrices for every cube. 
	for (int i = 0; i < RUBIKS_CUBE_SIZE; ++i)
		for (int j = 0; j < RUBIKS_CUBE_SIZE; ++j)
			for (int k = 0; k < RUBIKS_CUBE_SIZE; ++k)
			{
				// This cube's index in the rubiksCube.
				int cubeIndex = i * RUBIKS_CUBE_SIZE * RUBIKS_CUBE_SIZE + j * RUBIKS_CUBE_SIZE + k;
				m_cubeIndexes[i][j][k] = cubeIndex;

				// Rotational matrix for this cube.
				m_rotations[cubeIndex] = mat4(1.0);

				// Partial rotational angle this cube is in, between 0 and 90 degrees for every axis.
				m_partialRotations[cubeIndex] = vec3(0.0f);
			}
}

/**
* Validate the rotation of the given face.
*
* @param axisIdx The index of the axis to rotate around.
* @param col The index of the face to rotate around the given axis (RUBIKS_CUBE_SIZE possibilites).
* @param face The face we're trying to rotate .
*/
bool RubiksCube::validateFaceRotation(int axisIdx, int col, int face[RUBIKS_CUBE_SIZE][RUBIKS_CUBE_SIZE])
{
	bool validStatus = true;
	int cubeIndex, i, j, idx1, idx2, idx3;
	vec3 facePartialRotation, cubePartialRotation;

	// Iterate all the cubes in this face and make sure they are all partially rotated the same amount.
	for (i = 0; i < RUBIKS_CUBE_SIZE; i++)
		for (j = 0; j < RUBIKS_CUBE_SIZE; j++)
		{
			switch (axisIdx)
			{
			case(0):
				idx1 = col, idx2 = i, idx3 = j;
				break;
			case(1):
				idx1 = i, idx2 = col, idx3 = j;
				break;
			case(2):
				idx1 = i, idx2 = j, idx3 = col;
				break;
			}

			cubeIndex = m_cubeIndexes[idx1][idx2][idx3];
			cubePartialRotation = m_partialRotations[cubeIndex];

			// Set facePartialRotation to the first cube's partial rotation.
			if (i == 0 && j == 0)
			{
				facePartialRotation = cubePartialRotation;
			}
			
			// If not all the cubes in this face have the same partial rotation angle then some cubes are already partially rotated while others aren't.
			if (facePartialRotation != cubePartialRotation)
			{
				validStatus = false;
				break;
			}
		}
	return validStatus;
}

/**
* Rotate a single face in the rubiksCube.
*
* @param axisIdx The index of the axis to rotate around.
* @param col The index of the face to rotate around the given axis (RUBIKS_CUBE_SIZE possibilites).
* @param direction The direction to rotate the face, 1 = clockwise, -1 = counter clockwise .
*/
void RubiksCube::rotateFace(int axisIdx, int col, int direction) 
{
	int cubeIndex, i, j, idx1, idx2, idx3;
	float previousPartialRotation;
	vec3 axis;

	// In case the angleis 180, we change the angle to 90 and call rotateFace twice and then set the angle back to 180.
	if (m_angle == 180)
	{
		m_angle = 90.0f;
		rotateFace(axisIdx, col, direction);
		rotateFace(axisIdx, col, direction);
		m_angle = 180.0f;
		return;
	}

	// Hold the cubeIndexes of the face we're rotating.
	int face[RUBIKS_CUBE_SIZE][RUBIKS_CUBE_SIZE];
	for (i = 0; i < RUBIKS_CUBE_SIZE; i++)
		for (j = 0; j < RUBIKS_CUBE_SIZE; j++)
		{
			switch (axisIdx)
			{
			case(0):
				idx1 = col, idx2 = i, idx3 = j;
				break;
			case(1):
				idx1 = i, idx2 = col, idx3 = j;
				break;
			case(2):
				idx1 = i, idx2 = j, idx3 = col;
				break;
			}
			face[i][j] = m_cubeIndexes[idx1][idx2][idx3];
		}

	if (!validateFaceRotation(axisIdx, col, face))
	{
		return;
	}

	for (i = 0; i < RUBIKS_CUBE_SIZE; i++)
		for (j = 0; j < RUBIKS_CUBE_SIZE; j++)
		{
			switch (axisIdx)
			{
				case(0):
					axis = X_AXIS;
					idx1 = col, idx2 = i, idx3 = j;
					break;
				case(1):
					idx1 = i, idx2 = col, idx3 = j;
					axis = Y_AXIS;
					break;
				case(2):
					idx1 = i, idx2 = j, idx3 = col;
					axis = Z_AXIS;
					break;
			}

			cubeIndex = m_cubeIndexes[idx1][idx2][idx3];
			previousPartialRotation = m_partialRotations[cubeIndex][axisIdx];
			m_partialRotations[cubeIndex][axisIdx] += direction * m_angle;

			// Once we've rotated 90 degrees, change cubeIndexes and update the rotations mat.
			if ((int)(m_partialRotations[cubeIndex][axisIdx]) % 90 == 0)
			{
				// Swap the indexes in the m_cubeIndexes now that the cubes have fully rotated 90 degrees.
				if (direction == 1)
				{
					m_cubeIndexes[idx1][idx2][idx3] = face[j][RUBIKS_CUBE_SIZE - i - 1];
				}
				else
				{
					m_cubeIndexes[idx1][idx2][idx3] = face[RUBIKS_CUBE_SIZE - j - 1][i];
				}

				// In case our preivous rotation was a full 90 degrees, don't take into account the m_partialRotations in this face rotation.
				if (previousPartialRotation == 0)
				{
					m_rotations[m_cubeIndexes[idx1][idx2][idx3]] = rotate(direction * m_angle, axis) * m_rotations[m_cubeIndexes[idx1][idx2][idx3]];
				}
				else
				{
					m_rotations[cubeIndex] = rotate(m_partialRotations[cubeIndex][axisIdx], axis) * m_rotations[cubeIndex];
				}
				m_partialRotations[cubeIndex][axisIdx] = 0.0f;
			}			
		}
}

void RubiksCube::draw()
{
	float halfSize = CUBE_SIZE / 2.0f;

	// Iterate over all the cubes in the rubiksCube = RUBIKS_CUBE_SIZE^3.
	// Calculate for every cube its position, rotation and size and draw it.
	for (int i = 0; i < RUBIKS_CUBE_SIZE; i++)
		for (int j = 0; j < RUBIKS_CUBE_SIZE; j++)
			for (int k = 0; k < RUBIKS_CUBE_SIZE; k++)
			{
				mat4 t = mat4(1.0);

				// Translate this cube to its position in its face.
				t = translate(t, vec3((i - 1) * halfSize, (j - 1) * halfSize, (k - 1) * halfSize));

				mat4 cube_rotation = m_rotations[m_cubeIndexes[i][j][k]];
				m_scene->setMainMat(t * cube_rotation);

				// Calculate the partial rotations for every axis of this cube.
				mat4 x = rotate(m_partialRotations[m_cubeIndexes[i][j][k]].x, X_AXIS);
				mat4 y = rotate(m_partialRotations[m_cubeIndexes[i][j][k]].y, Y_AXIS);
				mat4 z = rotate(m_partialRotations[m_cubeIndexes[i][j][k]].z, Z_AXIS);

				// Render this cube with the updated MVP.
				m_scene->setMainMat(z * y * x * t * m_scene->getMainMat());
				m_scene->muliplyMVP();
				m_shader->Bind();
				m_shader->Update(mat4(m_scene->getMVP()), mat4(m_scene->getMainMat()));

				m_cube->draw();
			}
}

SceneData* RubiksCube::getScene()
{
	return m_scene;
}

float RubiksCube::getAngle()
{
	return m_angle;
}

void RubiksCube::setAngle(float angle)
{
	m_angle = angle;
}

void RubiksCube::printFace(int arr[RUBIKS_CUBE_SIZE][RUBIKS_CUBE_SIZE])
{
	cout << " --------- \n";
	for (int i = 0; i < RUBIKS_CUBE_SIZE; i++)
	{
		for (int j = 0; j < RUBIKS_CUBE_SIZE; j++)
		{
			cout << " " << arr[i][j] << " ";
		}
		cout << "\n";
	}
	cout << " --------- \n";
}

void RubiksCube::printRubiksCube(int arr[RUBIKS_CUBE_SIZE][RUBIKS_CUBE_SIZE][RUBIKS_CUBE_SIZE])
{
	for (int i = 0; i < RUBIKS_CUBE_SIZE; i++)
	{
		printFace(arr[i]);
	}
}

RubiksCube::~RubiksCube()
{
}