#pragma once
#include <Cube.h>
#include "shader.h"
#include <SceneData.h>
#include <iostream>

// Size can be 2 - 5.
static const int RUBIKS_CUBE_SIZE = 3;

static const float CUBE_SIZE = 2.0f;

static const vec3 X_AXIS = vec3(1, 0, 0);
static const vec3 Y_AXIS = vec3(0, 1, 0);
static const vec3 Z_AXIS = vec3(0, 0, 1);

using namespace std;

class RubiksCube
{
	public:
		RubiksCube(int width, int height);
		void rotateFace(int axis, int col, int direction);
		SceneData* getScene();
		void setAngle(float _angle);
		float getAngle();
		void draw();

		~RubiksCube();

	private:
		Cube* m_cube;
		SceneData* m_scene;
		Shader* m_shader;
		float m_angle;

		mat4 m_rotations[RUBIKS_CUBE_SIZE*RUBIKS_CUBE_SIZE*RUBIKS_CUBE_SIZE];
		vec3 m_partialRotations[RUBIKS_CUBE_SIZE*RUBIKS_CUBE_SIZE*RUBIKS_CUBE_SIZE];
		int m_cubeIndexes[RUBIKS_CUBE_SIZE][RUBIKS_CUBE_SIZE][RUBIKS_CUBE_SIZE];
		
		void printFace(int arr[RUBIKS_CUBE_SIZE][RUBIKS_CUBE_SIZE]);
		void printRubiksCube(int arr[RUBIKS_CUBE_SIZE][RUBIKS_CUBE_SIZE][RUBIKS_CUBE_SIZE]);
		bool validateFaceRotation(int axisIdx, int col, int face[RUBIKS_CUBE_SIZE][RUBIKS_CUBE_SIZE]);

};