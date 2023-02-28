#include "Mesh.h"

using namespace RenderMe::RenderMe3D;

Mesh::Mesh()
{

}

Mesh::Mesh(std::vector<Vertex> p_vertices)
	: m_vertices(p_vertices)
{
	for (Index i = 0; i < p_vertices.size(); i++)
		m_indices.push_back(i);
}

Mesh::Mesh(std::vector<Vertex> p_vertices, std::vector<Index> p_indices)
	: m_vertices(p_vertices),m_indices(p_indices)
{

}

Mesh::~Mesh()
{

}

void RenderMe::RenderMe3D::Mesh::addVertex(Vertex p_vertex)
{
	m_vertices.push_back(p_vertex);
}

void RenderMe::RenderMe3D::Mesh::addIndex(Index p_index)
{
	m_indices.push_back(p_index);
}

void RenderMe::RenderMe3D::Mesh::setVertex(Vertex p_vertex, int p_index)
{
	m_vertices[p_index] = p_vertex;
}

void RenderMe::RenderMe3D::Mesh::setIndex(Index p_index, int p_i)
{
	m_indices[p_i] = p_index;
}

void RenderMe::RenderMe3D::Mesh::setVertices(std::vector<Vertex> p_vertices)
{
	m_vertices = p_vertices;
}

void RenderMe::RenderMe3D::Mesh::setIndices(std::vector<Index> p_indices)
{
	m_indices = p_indices;
}
