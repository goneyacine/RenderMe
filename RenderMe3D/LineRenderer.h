#pragma once
#include <vector>
#include "Vectors.h"
#include "Vertex.h"
#include "Index.h"
using namespace RenderMe::Base;

//This line renderer is very basic and it needs to be improved in the future
namespace RenderMe
{
	namespace RenderMe3D
	{
		class LineRenderer
		{
		public :
			LineRenderer();
			LineRenderer(unsigned int p_vertexShader, unsigned int p_fragmentShader,Vector4 p_color = {.5f,0,.5f,1});
			LineRenderer(std::vector<Vector3> p_points,unsigned int p_vertexShader, unsigned int p_fragmentShader, Vector4 p_color = { .5f,0,.5f,1 });

			void addPoint(Vector3 p_point);
			void removePoint(int p_index);
			void addPoints(std::vector<Vector3> p_points);
			void removePoints(std::vector<int> p_indices);
			void setPoint(int p_index, Vector3 p_point);
			Vector3 getPoint(int p_index);
			std::vector<Vector3> getPoints();
			void setShaders(unsigned int p_vertexShader, unsigned int p_fragmentShader);
			unsigned int getShaderProgram();
			void setThikness(float p_thikness);
			void setColor(Vector4 p_color);
			Vector4 getColor();
			float getThikness();
			std::vector<Vertex> getVertices();
			std::vector<Index> getIndices();

		private :
			unsigned int m_shaderProgram;
			float m_thikness = 1;
			std::vector<Vertex> m_vertices;
			std::vector<Index> m_indices;
			std::vector<Vector3> m_points;
			Vector4 m_color = { .5f,0,.5f,1 };

		};
	}
}
