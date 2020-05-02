
#pragma once

#include "mesh.h"

using namespace glm;

class Cube
{
	public:
		Cube(float x, float y, float z, float size);
		void draw();
		~Cube();

	private:
		void initVertices(float x, float y, float z, float size);
		void initIndices();

		Vertex* m_vertices;
		unsigned int m_indices [36];
};
