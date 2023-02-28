#pragma once

#include <vector>

#include "Vertex.h"
#include "Index.h"

namespace RenderMe
{
	namespace RenderMe3D
	{
		//I used made the mesh a class instead of a struct to may add some functions later on like extrude, delete face...
		class Mesh
		{
		public :
			Mesh();
			Mesh(std::vector<Vertex> p_vertices);
			Mesh(std::vector<Vertex> p_vertices, std::vector<Index> p_indices);
			~Mesh();

			void addVertex(Vertex p_vertex);
			void addIndex(Index p_index);

			void setVertex(Vertex p_vertex, int p_index);
			void setIndex(Index p_index, int p_i);

			void setVertices(std::vector<Vertex> p_vertices);
			void setIndices(std::vector<Index> p_indices);
		private :
			std::vector<Vertex> m_vertices;
			std::vector<Index> m_indices;
		};
	}
}